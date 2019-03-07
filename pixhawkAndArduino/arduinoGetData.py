from threading import Thread
import serial as si
from .Extras.PID import PID
import numpy as np

class arduinoGetData:

    def __init__(self, com='COM8', baudRate = 9600, target_pressure=0, motor_speed=[1400, 1600]):
        self.depth = 0
        self.pressure = 0
        self.target_pressure = target_pressure
        self.yaw = 0
        self.run = True
        self.arduino = si.Serial(com, baudRate)
        self.max_forward_speed = motor_speed[1]
        self.max_reverse_speed = motor_speed[0]
        self.stop_speed = (motor_speed[0]+motor_speed[1])/2
        self.pixhawk_speed = self.stop_speed

        self.P = 2
        self.I = 0.01
        self.D = 0.5
        self.pid = PID.PID(self.P, self.I, self.D)
        self.pid.SetPoint = target_pressure
        self.pid.setSampleTime(1)

    def start(self):
        Thread(target=self.get, args=()).start()
        return self

    def get(self):
        while self.run:
            try:
                self.arduino.flush()
                data = self.arduino.readline().split(b',')
                self.pressure = float(data[0])
                self.yaw = float(data[1])
                self.depth = self.pressure
                # print (self.pressure, self.yaw)

                if not self.depth == 0:
                    self.motor_speed()
            except:
                pass

    def motor_speed(self):
        self.pid.update(self.pressure)
        self.pixhawk_speed = np.interp(self.pid.output, [-100, 100], [self.max_reverse_speed, self.max_forward_speed])

        # pressure_difference = self.target_pressure - self.pressure
        # print(self.pixhawk_speed, pressure_difference, self.target_pressure, self.pressure)
        # self.pixhawk_speed -= pressure_difference
        # # self.pixhawk_speed = int(self.pixhawk_speed)
        #
        # if self.pixhawk_speed > self.max_forward_speed:
        #     self.pixhawk_speed = self.max_forward_speed
        # elif self.pixhawk_speed<self.max_reverse_speed:
        #     self.pixhawk_speed = self.max_reverse_speed
        #
        # if abs(pressure_difference) < .5:
        #     self.pixhawk_speed = self.stop_speed

    def stop(self):
        self.run = False