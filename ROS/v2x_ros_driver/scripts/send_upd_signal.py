#!/usr/bin/env python
import rospy
import json
from v2x_ros_driver.msg import V2X
import socket

def callback(data):
    host = '192.168.105.209'
    port = 9999
    dest_addr = (host, port)
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    dict_var={}
    dict_var["Latitude"] = data.latitude
    dict_var["Longtitude"] = data.longtitude
    dict_var["Speed"] = data.speed
    dict_var["Heading"] = data.heading
    msg = json.dumps(dict_var)
    udp_socket.sendto(msg.encode('utf-8'), dest_addr)
    udp_socket.close()
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.latitude)
    
def listener():
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("V2X_msg", V2X, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
