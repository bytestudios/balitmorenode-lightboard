balitmorenode-lightboard
========================

An arduino sketch and python scripts to manage a large lightboard of GE Color Effects lights

GE Color Effects Light Board
----------------------------

The Node's lightboard is a 47x24 pixel series of GE Color Effects lights, a total of 48 strands,
each with either 24 or 23 strings.  The lights themselves are controlled by an Arduino Mega 2560
using 48 ports of the A, B, C, F, L and K port registers.  The Arduino Mega is the slave controlled by
its serial port, though USB, via either any computer or Raspberry Pi running Python.

In our case, the Raspberry Pi does the higher level processing of images, fonts, twitter feeds
and the like, and then processes what should go to the Mega's registers and sends that across the
serial wire.  The Pi is using pyserial, Pillow (new Image), and python-twitter.

### Light setup and data process ###

Each string of lights is a series of 23 or 24 single-addressable lights, each has a 6 byte address.
When you 'talk' to a string of lights, the first light listens for its address (and whatever
brightness / color data), and learns its address, then any addresses that come across the wire that's
not its address, it'll pass to the second light, which will learn its address, and then pass any
subsequent addresses along.

The full data length is 20 bit, 6 for its address, 8 for brightness and 12 for its color, specifically,
in order, 4 for blue, 4 for green and 4 for red.  For each bit, start 10us on, then 10us off, then
10us of the 'byte' and then 10us off. At the end of the 20 bits, turn off for its break time, 25-35us.
Getting the speed in microseconds is somewhat difficult, the hardware itself may take more than 10us
to turn on and off the power, say, or to read memory.  As such, an oscilloscope will help you find out
how long things are taking and asjust as necessary.

Thus:


    |000001|0111111|1111|0000|0111
    |------|-------|----|----|----
    |Bulb  |Bright |Blue|Grn |Red
    |=1    |=127*  |15  |0   |7


*Maximum brightness should be 127, going higher can reportedly burn out a light

In order for a strand to be written, assuming the strand is 24 lights, you'll send 24 x 20 bytes. Each
register is a series of 8 strands, so it's much more effective to use PORTA, etc. to send 8 lights at
a time, and in our case we're sending 3 ports, 24 lights, at the same time.  See Mega2560-pin-map.png
for a mapping of the pins.

### Data across the serial ###

We don't send any bulb addresses across the serial, the order of of which things are received is how
the Arduino Mega knows a bulb's address.

The data actually coming across the serial is a series of ascii characters constructed (struct packed) from
the bytes to be sent.  Thus, if you want to turn on all the registers (0b11111111), you'd send chr(255).
If you wanted 0b01001000, you'd send chr(72), which is incidentally the capital letter H.

Our board is laid out like this, each box is four strands

    |-------------------|-------------------|
    |PORTB              |PORTA              |
    |-------------------|-------------------|
    |PORTL              |PORTF              |
    |-------------------|-------------------|
    |PORTL              |PORTF              |
    |-------------------|-------------------|
    |PORTB              |PORTC              |
    |-------------------|-------------------|
    |PORTK              |PORTC              |
    |-------------------|-------------------|
    |PORTK              |PORTA              |
    |-------------------|-------------------|`

### Arduino Mega code ###

The Mega's code has some extra parts to it, but the setup function first paints the board in the order
we want the bulbs to be painted, so sendsome_left and sendsome_right just send the same data to all left
or right banks, and our case, 0b00000001000011001000 + a brightness, so it just gets brighter.

the Mega's serial awaits 60 chars, enough for a bulb paint for three strands (20 bytes in 3 registers) and
then paints that bulb in either the left or right strand.  Then it awaits for the next 60, et on.

For the moment, paint_array(), send_a_column() and send_string_data() are not used, but will be for
an Arduino-only mode (tbd), if there's no serial commands, say.

### Python code ###

control.py is the proof of concept that this works, and can send a variety of things to the board.

convertImageToPins(image, x-offset) takes an image array and breaks it apart into the requisite
registers and returns the serial output of the first 47 columns.  x-offset is the offset where
to start that send.  sendSerialToArduino sends that output across the serial port.

createTextPage(this_text, font_file, font_size, this_x, this_y) creates an image with text on it, with
attributes including which font, what size, and the x/y position.  panAndDisplayLongText takes any
width >47 image and pans the image by sending each panned part across to convertImageToPins

The rest of the, for now, just reads the most recent Twitter post for balitmorenode and displays it,
panning it across the page.  getTwitterStatus(n) gets the nth most recent post.
