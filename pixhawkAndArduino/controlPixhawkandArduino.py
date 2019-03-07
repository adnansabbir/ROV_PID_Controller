import time
from pymavlink import mavutil
import pixhawkAndArduino.arduSub_pymavlink_methods as pixhawk
from pixhawkAndArduino.arduinoGetData import arduinoGetData

print("Setting up Arduino")
throttle = arduinoGetData(com='COM3', target_pressure=-5)

print("Setting up Pixhawk")
# Create the connection
# Need to provide the serial port and baudrate
auv = mavutil.mavlink_connection('COM5')
auv.wait_heartbeat()
time.sleep(2)

print("Calibrating level")
# Calibrating the level
auv.calibrate_level()

print("Arming the AUV")
auv.arducopter_arm()
print("Going to Stablize Mode in 3 sec")
time.sleep(3)

# Set to STABILIZE mode
pixhawk.change_mode(auv, 'STABILIZE')

print("Started depth sensing and throttle count")
# Start depth sensing and throttle calculation
throttle.start()


print("Going to target depth")
# Go to target depth First
print(throttle.target_pressure,throttle.pressure)
while throttle.pressure > throttle.target_pressure:
    print(throttle.pixhawk_speed,throttle.pressure, throttle.target_pressure)
    pixhawk.set_rc_channel_pwm(auv, 3, int(throttle.pixhawk_speed))
    time.sleep(.1)

# master.calibrate_level()
#

while True:
    pixhawk.set_rc_channel_pwm(auv, 3, int(throttle.pixhawk_speed))
    print (throttle.pixhawk_speed, throttle.depth, throttle.yaw)
    # pass