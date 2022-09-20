#coding=utf-8
import paramiko
from time import sleep
import re

class operator_shell_command:
        def __init__(self):
            self._transport = None
            self._channel = None
        def transport_connect(self,info):
            self._transport = paramiko.Transport((info[0], int(info[1])))  # 建立一个加密的管道
            self._transport.start_client()
            # 用户名密码方式
            self._transport.auth_password(info[2], info[3])
            # 打开一个通道
            self._channel = self._transport.open_session()
            self._channel.settimeout(7200)
            # 获取一个终端
            self._channel.get_pty()
            # 激活器
            self._channel.invoke_shell()
            return self._transport,self._channel
        def transport_disconnect(self):
            if self._channel:
                self._channel.close()
            if self._transport:
                self._transport.close()
        def send(self,cmd,channel):
            commod = cmd
            cmd += '\r'
            # 通过命令执行提示符来判断命令是否执行完成
            p = re.compile(r']#')
            result = ''
            # 发送要执行的命令
            channel.send(cmd)
            # 回显很长的命令可能执行较久，通过循环分批次取回回显
            while True:
                sleep(0.2)
                ret = channel.recv(65535)
                ret = ret.decode('utf-8')
                result += ret
                print ret
                if p.search(ret):
                    break
            # print(commod+'结束')
            return result
        def sendMiddle(self,cmd,channel):
            commod = cmd
            cmd += '\r'
            # 通过命令执行提示符来判断命令是否执行完成
            # 发送要执行的命令
            channel.send(cmd)
            # 回显很长的命令可能执行较久，通过循环分批次取回回显
            sleep(0.5)
            ret = channel.recv(65535)
            ret = ret.decode('utf-8')
            # printLine(commod + '结束')
            print ret
            return ret


info = ['XXX.XXX.XXX.XXX','22','ktest','porsche']
transport = operator_shell_command()
channel = transport.transport_connect(info)[1]
transport.send('cd Desktop/ktest-2.0.2/',channel)
str1=transport.sendMiddle('sudo robot tests/usecases/emobility/cevc/cevc.robot',channel)
if 'password' in str1:
     str2 = transport.sendMiddle('porsche',channel)
while True:
    if 'yes' in str2:
        str2=transport.sendMiddle('yes',channel)
