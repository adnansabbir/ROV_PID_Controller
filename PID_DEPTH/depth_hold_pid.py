from PID_DEPTH.PID import PID
import time
import serial

ser = serial.Serial('/dev/tty.usbserial', 9600)

def mapFromTo(x, a, b, c, d):
    if x < a:
        x = a
    if x > b:
        x = b

    y = (x - a) / (b - a) * (d - c) + c
    if x < c:
        x = c
    if x > d:
        x = d
    return int(y)


targetAlt = 100
currentAlt = 0
data = [0.0, 0.0]
motorMax = 1800
motorMin = 1200

P = 2
I = 0.01
D = 0.5

pid = PID.PID(P, I, D)
pid.SetPoint = targetAlt
pid.setSampleTime(1)



while 1:
    data = ser.readline().split(' , ')
    currentAlt = data[0]

    pid.update(currentAlt)
    output = pid.output
    # m=interp(output,[-100,100],[1100,1900])  #this uses numpy library
    throttle = mapFromTo(output, -100, 100, motorMin, motorMax)  # custom method

    print("Target: %.1f cm | Current: %.1f cm | PPM: %s " % (targetAlt, currentAlt, throttle) + "raw_PID:" + str(output))

    time.sleep(0.5)


