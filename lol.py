import serial
ser = serial.Serial('/dev/ttyACM2',9600)

while 1:
	print("\nhello")
#	line=ser.read(5)
	ser.write(b'a')
	print("\nSent\n")
