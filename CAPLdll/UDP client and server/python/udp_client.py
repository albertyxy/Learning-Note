import socket
import json
import random

# 1. 创建udp套接字
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# 2. 准备接收方的地址
# '127.0.0.1'表示目的ip地址
# 9999表示目的端口
dest_addr = ('192.168.209.129', 9999)  # 注意 是元组，ip是字符串，端口是数字
#发送json消息
dict_var={
    'Latitude': 800000000,
    'Longtitude':1500000000,
    'Transmission': 2,
    'Speed': 2000,
    'Heading': 28000,
    'Acc_Lat': -1500,
    'Acc_Lng': 1500,
    'Veh_Class': 200,
    #'Events': '0',
    'Response_Type': 2,
    'Lights_Use': 2
}
while True:
    # 建立客户端连接
    dict_var["Latitude"] = random.randint(0,900000000)
    dict_var["Longtitude"] = random.randint(0,1800000000)
    dict_var["Speed"] = random.randint(0, 8191)
    dict_var["Heading"] = random.randint(0, 28800)
    msg = json.dumps(dict_var)
    # 4. 发送数据到指定的电脑上的指定程序中
    udp_socket.sendto(msg.encode('utf-8'), dest_addr)
    if msg == "":
        print("close UDP connection")
        break
# 5. 关闭套接字
udp_socket.close()