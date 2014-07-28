from PIL import Image
from numpy import array
import numpy as np
import struct
import serial, time

ser = serial.Serial('/dev/ttyACM0', 57600)
time.sleep(2)

size = 47, 24
#img = Image.open("47x24.png")
img = Image.open("lilbit.jpg")
#img = Image.open("fish.jpg")
print img.size
#img.thumbnail(size, Image.ANTIALIAS)
#img.save("kitten.thumb.jpg", "JPEG")
#array.set_printoptions(formatter={'int':hex})
arr = array(img)# many an array out of the image
arr = zip(*arr) # flip axis to read column at a time
brightness = 126976 # default brightness (for now) (max 111110 253952)
column_i = 0
mypacketA = []
mypacketB = []
mypacketC = []
mypacketF = []
mypacketL = []
mypacketK = []
for column in arr:
	left_bank = 1 if column_i<23 else 0 #left or right
	print '----line {}----'.format(column_i)
	# iterate through bytes

	# iterate through pixels, save into cdata
	cdata = []
	for j in range(0,24):
		bright = (int)(column[j][0] + column[j][1]+ column[j][2]) / 12 * 4096
		cdata.append((column[j][0]/16) + ((column[j][1]/16) << 4) + ((column[j][2]/16) << 8) + brightness)
		if j < 24 and column_i == 0:
			print column[j]
			print column[j][0]/16
			print column[j][1]/16
			print column[j][2]/16
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
		mypacketB.append(portb)
		mypacketC.append(portc)
		mypacketF.append(portf)
		mypacketL.append(portl)
		mypacketK.append(portk)


	column_i += 1
	#print 'packet: {}'.format(len(mypacketE))
	#print len(mypacketD)
	if column_i < 24:
		ser.write ([chr(i) for i in mypacketB])
		ser.write ([chr(i) for i in mypacketK])
		ser.write ([chr(i) for i in mypacketL])
	else:
		ser.write ([chr(i) for i in mypacketA])
		ser.write ([chr(i) for i in mypacketC])
		ser.write ([chr(i) for i in mypacketF])
	mypacketA = []
	mypacketB = []
	mypacketC = []
	mypacketF = []
	mypacketL = []
	mypacketK = []
	#if column_i == 30: break

#vhex = np.vectorize(hex)
#print mypacket
#print len(mypacket)
#for i in mypacket:
#	print i
#ser.write ([chr(i) for i in mypacket])

#valueout = ""
#while 1:
	#valuecount += 1
#	value = ser.read()
	#print value
#	valueout += value;
#	if value == '\n':
#		print valueout
#		valueout = ""
		#valuecount = 0

ser.close()
