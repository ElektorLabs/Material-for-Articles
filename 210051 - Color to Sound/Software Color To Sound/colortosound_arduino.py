# colortosound_arduino.py
import serial, time
# ser=serial.Serial("COM3",9600,timeout=1)
# ser=serial.Serial("/dev/cu.usbserial-1410",9600,timeout=1)
ser=serial.Serial("/dev/ttyUSB0",9600,timeout=1)
time.sleep(3); ser.write(b"color?\n")
time.sleep(2); reply=ser.readlines()
# print((reply[0]))
colors = reply[0].split()
for i, entry in enumerate(colors):
    colors[i]= int(entry.decode('utf-8').replace('\r\n', ''))
#print(colors)
intensity = colors [0]; red = colors [1]
green = colors [2]; blue = colors [3]
if red/intensity > 0.6:
    ser.write(b"tone_red\n")
elif green/intensity > 0.3:
    ser.write(b"tone_green\n")
elif blue/intensity > 0.24:
    ser.write(b"tone_blue\n")
else:
    ser.write(b"no_color\n")
ser.close()
