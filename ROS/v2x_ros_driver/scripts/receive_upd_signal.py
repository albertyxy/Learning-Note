#!/usr/bin/env python
# license removed for brevity
import rospy
import json
import socket
from v2x_ros_driver.msg import V2X


def talker():
    host = ''
    port = 9999
    dest_addr = (host, port)
    msg_to_send=V2X()
    pub = rospy.Publisher('V2X_msg', V2X, queue_size=50)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 10hz
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(dest_addr)
    while not rospy.is_shutdown():
        #receive less than 1024 Byte
        msg, addr = s.recvfrom(1024)
        msg = msg.decode('utf-8')
        f = json.loads(msg)
        if "Latitude" in f:
            msg_to_send.latitude=f["Latitude"]
        if "Longtitude" in f:
            msg_to_send.longtitude=f["Longtitude"]
        if "Transmission" in f:
            msg_to_send.transmission_state=f["Transmission"]
        if "Speed" in f:
            msg_to_send.speed=f["Speed"]
        if "Heading" in f:
            msg_to_send.heading=f["Heading"]
        if "Acc_Lat" in f:
            msg_to_send.latitude_acceleration=f["Acc_Lat"]
        if "Acc_Lng" in f:
            msg_to_send.longtitude_acceleration=f["Acc_Lng"]
        if "Veh_Class" in f:
            msg_to_send.vehicle_class=f["Veh_Class"]
        if "Events" in f:
            msg_to_send.events=f["Events"]
        if "Response_Type" in f:
            msg_to_send.response_type=f["Response_Type"]
        if "Lights_Use" in f:
            msg_to_send.light_use=f["Lights_Use"]
        
        rospy.loginfo(msg_to_send)
        pub.publish(msg_to_send)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
