from pymavlink import mavutil
import time

# This functions changes mode of the pixhawk
def change_mode(master, mode):
    #############################################################set mode :
    # Choose a mode
    # mode = 'STABILIZE'

    # Check if mode is available
    if mode not in master.mode_mapping():
        print('Unknown mode : {}'.format(mode))
        print('Try:', list(master.mode_mapping().keys()))
        exit(1)

    # Get mode ID: return value should be 1 for acro mode
    mode_id = master.mode_mapping()[mode]
    master.mav.set_mode_send(
        master.target_system,
        mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,
        mode_id)

############################################################## function to send RC values for movement
# RC channel list https://www.ardusub.com/operators-manual/rc-input-and-output.html
def set_rc_channel_pwm(master, id, pwm=1500):
    """ Set RC channel pwm value
    Args:
        id (TYPE): Channel ID
        pwm (int, optional): Channel pwm value 1100-1900
    """

    # 1 Pitch
    # 2 Roll
    # 3 Throttle
    # 4 Yaw
    # 5 Forward
    # 6 Lateral
    # 7 Camera Pan
    # 8 Camera Tilt
    # 9 Lights
    # 1 Level
    # 10 Lights
    # 2 Level
    # 11 Video Switch

    if id < 1:
        print("Channel does not exist.")
        return

    # We only have 8 channels
    #http://mavlink.org/messages/common#RC_CHANNELS_OVERRIDE
    if id < 9:
        rc_channel_values = [65535 for _ in range(8)]
        rc_channel_values[id - 1] = pwm
        master.mav.rc_channels_override_send(
            master.target_system,                # target_system
            master.target_component,             # target_component
            *rc_channel_values)                  # RC channel list, in microseconds.

def get_raw_depth(master):
    time.sleep(.001)
    msg = master.recv_match()

    if msg.get_type() == 'SCALED_PRESSURE2':
        depth = msg.to_dict()['press_abs']
        return depth