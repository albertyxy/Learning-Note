import json
import socket

def main():
    # 创建udp套接字
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 准备接收方的地址
    # dest_addr = ('127.0.0.1', 9999)  # 注意 是元组，ip是字符串，端口是数字
    localaddr = ("", 9999)
    udp_socket.bind(localaddr)
    while True:
        msg, addr = udp_socket.recvfrom(1024)  # 1024表示本次接收的最大字节数
        msg = msg.decode('utf-8')
        recvmsg = json.loads(msg)
        print(recvmsg)
        if msg == "":
            print("close UDP connection")
            break
    # 关闭套接字
    udp_socket.close()
if __name__ == "__main__":
    main()