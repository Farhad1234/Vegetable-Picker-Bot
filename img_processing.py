import cv2
#import serial
import numpy as np
cap=cv2.VideoCapture(0)
#s=serial.Serial('/dev/ttyUSB0',9600)
width=int(cap.get(3))
height=int(cap.get(4))
width=int(width/2)
height=int(height/2)
#s.write(width)
while 1:
	_, img = cap.read()
	hsv=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
	red_lower=np.array([135,98,41])#pre 150,20,20,bottle 135,98,41 #110 115 150 #0 215 40
	red_upper=np.array([255,255,255]) #130 255 255  # 179 255 255                       110,115,150,130,255,255
	red=cv2.inRange(hsv,red_lower,red_upper)
	
	kernal=np.ones((5,5)) ##
	red=cv2.erode(red,kernal)
	red=cv2.dilate(red,kernal)
	#res=cv2.bitwise_and(img,img,mask=red)
	#bmask = cv2.GaussianBlur(res, (5,5),0)
	median=cv2.medianBlur(red,15)
	#cv2.imshow('median',median)
	opening=cv2.morphologyEx(median ,cv2.MORPH_OPEN,kernal)
	#cv2.imshow('opening',opening)
	opening=cv2.morphologyEx(opening,cv2.MORPH_CLOSE,kernal)
	#cv2.imshow('opening1',opening)
	(_,contours, hierarchy)=cv2.findContours(opening,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
	opening=cv2.bitwise_and(img,img,mask=opening)
	if len(contours)>0:
		largest = 0
		area = 0
		for i in range(len(contours)):
			temp_area = cv2.contourArea(contours[i])
			if temp_area > area:
				area = temp_area
				largest = i
		coordinates = cv2.moments(contours[largest])
		x = int(coordinates['m10']/coordinates['m00'])
		y = int(coordinates['m01']/coordinates['m00'])
		diam = int(np.sqrt(area)/4)
		cv2.circle(opening,(x,y),diam,(0,255,0),1)
		cv2.line(opening,(x-2*diam,y),(x+2*diam,y),(0,255,0),1)
		cv2.line(opening,(x,y-2*diam),(x,y+2*diam),(0,255,0),1)
		#s.write(width)
		#if x > width :
		#	print ("clockwise")
			#print width
		#	print (x-width)
		#else:
		#	print ("anticlockwise")
		#	print (x-width)
			#print width
		print(x-width," ",-(y-height)," ",diam)
	cv2.imshow("color Tracking",img)
	#res=cv2.bitwise_and(img,img,mask=opening)
	cv2.imshow("rk",opening)
	if cv2.waitKey(10) & 0xFF ==ord('q'):
		cap.release()
		cv2.destroyAllWindows()
		break
