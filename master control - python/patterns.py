from math import ceil
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from numpy import array
import numpy as np
import struct
import serial
import time
import twitter
#import pygame
#from webkit2png import WebkitRenderer, init_qtgui

# to make pygame not have a screen
import os 
os.environ['SDL_VIDEODRIVER'] = 'dummy'

def find_arduino():
    locations=['/dev/cu.usbmodem1421','/dev/cu.usbmodem1411','/dev/ttyACM0',
               '/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',  
               '/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3',
               'COM1', 'COM2', 'COM3', 'COM4', 'COM5', 'COM6', 'COM7', 'COM8']
    try:
        import serial.tools.list_ports as list_ports
        locations += [port[0] for port in list_ports.comports()]
    except:
        pass

    for device in locations:    
        try:    
            print "Trying...",device
            #FIXME, opening this up is a kludge
            arduino = serial.Serial(device, 1000000)
            del arduino
            return device
        except:    
            print "Failed to connect on",device     
    print "Could not find arduino!"
    return None


def convertImgToArr(img):
	arr = array(img) # map an array out of the image
	#print arr
	arr = zip(*arr) # flip axis to read column at a time
	return arr


def convertArrToPins(arr, xoffset):
	brightness = 126976 # default brightness (for now) (max 111110 253952)
	column_i = 0

	serial_output = []
	mypacketA = []
	mypacketB = []
	mypacketC = []
	mypacketF = []
	mypacketL = []
	mypacketK = []

	for a in range(0+xoffset,47+xoffset):
		column = arr[a]
		left_bank = 1 if column_i<24 else 0 #left or right
		#print '----line {}----'.format(column_i)
		# iterate through pixels, save into cdata
		cdata = []
		for j in range(0,24):
			#bright = (int)(column[j][0] + column[j][1]+ column[j][2]) / 2 * 4096
			cdata.append((column[j][0]/16) + ((column[j][1]/16) << 4) + ((column[j][2]/16) << 8) + brightness)
		#	if j < 24 and column_i == 0:
		#		print column[j]
		#		print column[j][0]/16
		#		print column[j][1]/16
		#		print column[j][2]/16
		#print cdata

		for b in reversed(range(0,20)):
			porta = 0 #00000000
			portb = 0 #00000000
			portc = 0 #00000000
			portf = 0 #00000000
			portk = 0 #00000000
			portl = 0 #00000000

			for j in range(0,24):
				#if column_i==0: print column[j]
				thisbyte = (cdata[j] >> b) & 1
				if left_bank:
					if j==0 and thisbyte: portb = portb | 0b00000001;
					if j==1 and thisbyte: portb = portb | 0b00001000;
					if j==2 and thisbyte: portb = portb | 0b00000100;
					if j==3 and thisbyte: portb = portb | 0b00000010;
					if j==4 and thisbyte: portl = portl | 0b01000000;
					if j==5 and thisbyte: portl = portl | 0b10000000;
					if j==6 and thisbyte: portl = portl | 0b00010000;
					if j==7 and thisbyte: portl = portl | 0b00100000;
					if j==8 and thisbyte: portl = portl | 0b00000001;
					if j==9 and thisbyte: portl = portl | 0b00000010;
					if j==10 and thisbyte: portl = portl | 0b00000100;
					if j==11 and thisbyte: portl = portl | 0b00001000;
					if j==12 and thisbyte: portb = portb | 0b10000000;
					if j==13 and thisbyte: portb = portb | 0b01000000;
					if j==14 and thisbyte: portb = portb | 0b00100000;
					if j==15 and thisbyte: portb = portb | 0b00010000;
					if j==16 and thisbyte: portk = portk | 0b00000001;
					if j==17 and thisbyte: portk = portk | 0b00000010;
					if j==18 and thisbyte: portk = portk | 0b00000100;
					if j==19 and thisbyte: portk = portk | 0b00001000;
					if j==20 and thisbyte: portk = portk | 0b00010000;
					if j==21 and thisbyte: portk = portk | 0b00100000;
					if j==22 and thisbyte: portk = portk | 0b01000000;
					if j==23 and thisbyte: portk = portk | 0b10000000;
				else:
					if j==0 and thisbyte: porta = porta | 0b00001000;
					if j==1 and thisbyte: porta = porta | 0b00000100;
					if j==2 and thisbyte: porta = porta | 0b00000010;
					if j==3 and thisbyte: porta = porta | 0b00000001;
					if j==4 and thisbyte: portf = portf | 0b00000010;
					if j==5 and thisbyte: portf = portf | 0b00000001;
					if j==6 and thisbyte: portf = portf | 0b00001000;
					if j==7 and thisbyte: portf = portf | 0b00000100;
					if j==8 and thisbyte: portf = portf | 0b10000000;
					if j==9 and thisbyte: portf = portf | 0b01000000;
					if j==10 and thisbyte: portf = portf | 0b00100000;
					if j==11 and thisbyte: portf = portf | 0b00010000;
					if j==12 and thisbyte: portc = portc | 0b00000001;
					if j==13 and thisbyte: portc = portc | 0b00000010;
					if j==14 and thisbyte: portc = portc | 0b00000100;
					if j==15 and thisbyte: portc = portc | 0b00001000;
					if j==16 and thisbyte: portc = portc | 0b01000000;
					if j==17 and thisbyte: portc = portc | 0b00100000;
					if j==18 and thisbyte: portc = portc | 0b00010000;
					if j==19 and thisbyte: portc = portc | 0b10000000;
					if j==20 and thisbyte: porta = porta | 0b10000000;
					if j==21 and thisbyte: porta = porta | 0b01000000;
					if j==22 and thisbyte: porta = porta | 0b00100000;
					if j==23 and thisbyte: porta = porta | 0b00010000;
				#print '-' + bin(portl)

			mypacketA.append(porta)
			mypacketC.append(portc)
			mypacketF.append(portf)
			mypacketB.append(portb)
			mypacketL.append(portl)
			mypacketK.append(portk)


		#print 'packet: {}'.format(len(mypacketE))
		#print mypacketB
		if column_i < 24:
			serial_output.append(mypacketB)
			serial_output.append(mypacketK)
			serial_output.append(mypacketL)
		else:
			serial_output.append(mypacketA)
			serial_output.append(mypacketC)
			serial_output.append(mypacketF)
		mypacketA = []
		mypacketB = []
		mypacketC = []
		mypacketF = []
		mypacketL = []
		mypacketK = []

		column_i += 1
		#if column_i == 30: break
	return serial_output


def sendSerialToArduino(this_output):
	for serial_part in this_output:
		#print len(serial_part)
		time.sleep (.0005)
		#uncomment below to get a hex 'page' to hardcode into arduino
		#print '"'+"".join("\\x%02x" % i for i in serial_part)+'"'
		ser.write ([chr(i) for i in serial_part])


def createTextPage(this_text, font_file, font_size, this_x, this_y):
	# choose font and get its size
	font = ImageFont.truetype(font_file, font_size)
	text_width, text_height = font.getsize(this_text)
	img = Image.new('RGB', (text_width, 24), (16, 16, 16));
	draw = ImageDraw.Draw(img)
	#draw.line((0,0, 46,24), fill='#224400', width=3)
	#draw.line((0,24, 46,0), fill='#002244', width=3)
	#font = ImageFont.load_default()
  #font = ImageFont.truetype("pixel.ttf", 15)
	draw.text((this_x, this_y), this_text, font=font, fill=(255,181,40))
	#draw.text((this_x, this_y), this_text, font=font, fill=(255,181,40))
	#print text_width, text_height
	return img


def panAndDisplayLongText(display_text, offset_y):
	# create image that has whole tweet
	img = createTextPage(current_status, 'fonts/pixel.ttf', 14, 0, offset_y)
	image_x, image_y = img.size
	#page through the image
	for i in range(0, image_x - 47, 4):
		sendSerialToArduino(convertImageToPins(img, i))
	return 'done'


# def rainbow(d_lights):
# 	lights = yield d_lights
# 	tq_index = 0
# 	width, height = yield lights.d_size()
# 	surf = pygame.Surface((width,height))
# 	pixels = np.zeros([width,height,3], np.uint8)
# 	while True:
# 		#start rendering a cycle.
# 		yield lights.d_acquire()
# 		for p in xrange(0, 360*7, 5):
# 			for x in xrange(0, width):
# 				for y in xrange(0, height):
# 					p_rad = p/180.*3.14159
# 					hue = (2+math.sin(float(x)/width-p_rad/7+0.5)+math.sin(float(y)/height-p_rad))/4
# 					(r,g,b) = colorsys.hsv_to_rgb(hue,1,1)
# 					pixels[x,y,0] = int(255*r)
# 					pixels[x,y,1] = int(255*g)
# 					pixels[x,y,2] = int(255*b)
# 			pygame.surfarray.blit_array(surf,pixels)
# 			lights.d_display(surf)
# 			yield d_wait(0) #this returns control to twisted temporarily.
# 		lights.release()

ser = serial.Serial(find_arduino(), 1000000)
#ser = serial.Serial('/dev/ttyACM0', 1000000)
#ser = serial.Serial('/dev/cu.usbmodem1421', 1000000)
time.sleep(2)



# api = twitter.Api(consumer_key='',
#                       consumer_secret='',
#                       access_token_key='',
#                       access_token_secret='')
api = twitter.Api(consumer_key='AmRUpKG8WAdpHpQkhkPxZjCM6',
                      consumer_secret='bWmjiIpgSISs40haFI0i9rvwUFsYTjSzaVvLH8YmMqapYKXqzo',
                      access_token_key='20867831-DowaligUQju9o53wsrbKqrBUfRRgsqOO9PcuzZwGc',
                      access_token_secret='0oHr3XXZHTaP4rR8gGWVx9Wb3UPL0ilLSfj7yavW7UGrI')
#print api.VerifyCredentials()
statuses = api.GetUserTimeline(screen_name='@baltimorenode')

#rainbow()



# pygame.init()
# screen = pygame.display.set_mode((47,24), pygame.NOFRAME).convert()
# screen = screen.convert_alpha()
# #screen = pygame.image.load("images/fish.jpg")
# screen.fill([123,240,67])
# pygame.draw.circle(screen, [255, 0, 0],[23, 12], 8)
# myarray = pygame.surfarray.pixels3d(screen)
# sendSerialToArduino(convertArrToPins(myarray, 0))
# 
# screen.fill([123,240,67])
# pygame.draw.circle(screen, [255, 0, 0],[23, 12], 10)
# myarray = pygame.surfarray.pixels3d(screen)
# sendSerialToArduino(convertArrToPins(myarray, 0))


img = Image.new('RGB', (47, 24), (16, 16, 16));
draw = ImageDraw.Draw(img)
# draw.line((0,0, 46,24), fill='#224400', width=3)
# draw.line((0,24, 46,0), fill='#002244', width=3)
# sendSerialToArduino(convertArrToPins(convertImgToArr(img), 0))
# draw.rectangle((0,0,47,24), fill='#660066')
# sendSerialToArduino(convertArrToPins(convertImgToArr(img), 0))


def paintPacman(draw, x, y, size):
	curtime = time.time()
	pacmansize = int(ceil(10*(ceil(curtime) - curtime)) - 5) * 5
	print pacmansize
	draw.pieslice((x, y , x+size, y+size), 30+pacmansize, 330-pacmansize, fill="#ffff00")
	return draw


for i in range(0 ,20):
	draw.rectangle((3,3,44,21), fill='#000066')
	draw = paintPacman(draw, 4, 4, 10)
	sendSerialToArduino(convertArrToPins(convertImgToArr(img), 0))
	time.sleep(.001)


# time.sleep (.002)

#tempvalue = myarray[10][10]
# for i in range(0 ,20, 5):
# 	myarray = [[[ 22, 0+(row*4), 105] for col in range(24)] for row in range(47)]
# 	myarray[5][i] = [200,100,0]
# 	myarray[5][i+1] = [200,100,0]
# 	myarray[5][i+2] = [200,100,0]
# 	myarray[5][i+3] = [200,100,0]
# 	myarray[6][i] = [200,100,0]
# 	myarray[6][i+1] = [200,100,0]
# 	myarray[6][i+2] = [200,100,0]
# 	myarray[6][i+3] = [200,100,0]
# 	sendSerialToArduino(convertArrToPins(myarray, 0))
# 	time.sleep (.0005)

#myarray[10][10] = tempvalue
#sendSerialToArduino(convertArrToPins(myarray, 0))



#img = Image.open("images/fish.jpg")
#sendSerialToArduino(convertArrToPins(convertImgToArr(img), 0))
#img = Image.open("images/lilbit.jpg")
#sendSerialToArduino(convertImageToPins(img, 0))

ser.close()
