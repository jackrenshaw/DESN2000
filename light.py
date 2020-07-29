import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13, GPIO.OUT)         #LED output pin
GPIO.setup(15, GPIO.OUT)         #LED output pin
GPIO.setup(21, GPIO.IN)         #LED output pin
GPIO.setup(26, GPIO.IN)         #LED output pin

GPIO.output(13,1)
GPIO.output(15,1)
while True:
    #print("motor: "+str(GPIO.input(21)))
    print(GPIO.input(26))
