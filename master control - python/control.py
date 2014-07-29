from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from numpy import array
import numpy as np
import struct
import serial, time
import twitter

#ser = serial.Serial('/dev/ttyACM0', 1000000)
ser = serial.Serial('/dev/cu.usbmodem1421', 1000000)
time.sleep(2)

def convertImageToPins(img, xoffset):
	brightness = 126976 # default brightness (for now) (max 111110 253952)
	column_i = 0

	serial_output = []
	mypacketA = []
	mypacketB = []
	mypacketC = []
	mypacketF = []
	mypacketL = []
	mypacketK = []

	arr = array(img) # map an array out of the image
	arr = zip(*arr) # flip axis to read column at a time

	for a in range(0+xoffset,47+xoffset):
		column = arr[a]
		left_bank = 1 if column_i<23 else 0 #left or right
		#print '----line {}----'.format(column_i)
		# iterate through pixels, save into cdata
		cdata = []
		for j in range(0,24):
			bright = (int)(column[j][0] + column[j][1]+ column[j][2]) / 3 * 4096
			cdata.append((column[j][0]/16) + ((column[j][1]/16) << 4) + ((column[j][2]/16) << 8) + bright)
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


		column_i += 1
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
		#if column_i == 30: break
	return serial_output


def sendSerialToArduino(this_output):
	for serial_part in this_output:
		#print len(serial_part)
		time.sleep (.0015)
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
	img = createTextPage(current_status, 'pixel.ttf', 14, 0, offset_y)
	image_x, image_y = img.size
	#page through the image
	for i in range(0, image_x - 47, 4):
		sendSerialToArduino(convertImageToPins(img, i))
	return 'done'



api = twitter.Api(consumer_key='',
                      consumer_secret='',
                      access_token_key='',
                      access_token_secret='')
#print api.VerifyCredentials()
statuses = api.GetUserTimeline(screen_name='@baltimorenode')

img = Image.open("47x24.png")
#img = Image.open("lilbit.jpg")
#img = Image.open("fish.jpg")
#img = Image.new('RGBA', (47, 24), (30, 30, 30, 0));

#draw = ImageDraw.Draw(img)
#draw.line((0,0, 46,24), fill='#336600', width=3)
#draw.line((0,24, 46,0), fill='#003366', width=3)
#font = ImageFont.truetype("reflex.ttf", 15)
#draw.text((-1, 1), "hi node", font=font, fill=(255,131,0))
#img = Image.open("47x24.png")
draw = ImageDraw.Draw(img)
font = ImageFont.truetype("pixel.ttf", 14)
#font = ImageFont.truetype("reflex.ttf", 10)
draw.text((0, 0), "reading", font=font, fill=(200,200,200))
draw.text((18, 10), "serial", font=font, fill=(200,200,200))

sendSerialToArduino(convertImageToPins(img, 0))

# img = Image.new('RGBA', (47, 24), (20, 20, 20, 0));
# draw = ImageDraw.Draw(img)
# draw.line((0,0, 46,24), fill='#224400', width=3)
# draw.line((0,24, 46,0), fill='#002244', width=3)
# font = ImageFont.truetype("reflex.ttf", 10)
# draw.text((0, 4), "Hello Node.", font=font, fill=(255,181,40))
#img = Image.open("fish.jpg")
#time.sleep(5)
def getTwitterStatus(which):
	this_current_status = '--not connected--'
	i = 0
	for s in statuses:
		this_current_status = s.text
		#remove links
		if this_current_status.find('http://') > 0:
			this_current_status = this_current_status[:this_current_status.find('http://')]
		i += 1
		if i==which:
			return this_current_status
			break

current_status = getTwitterStatus(1)
panAndDisplayLongText(current_status, 1)

current_status = getTwitterStatus(2)
panAndDisplayLongText(current_status, 10)

current_status = getTwitterStatus(3)
panAndDisplayLongText(current_status, 5)


ser.close()
