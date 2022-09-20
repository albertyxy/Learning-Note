#coding=utf-8
import paramiko
import time
hostname='192.168.209.129'
port=22
username='albert'
password='6'
server_path="/home/albert/Downloads/carla_ros_bridge_with_example_ego_vehicle.png"
local_path="carla_ros_bridge_with_example_ego_vehicle.png"

# server_path="/home/albert/catkin_ws/"
# local_path="catkin_ws/"

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
try:
    ssh.connect(hostname, port, username, password)
    ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command("ls")
    time.sleep(1)
    sftp = ssh.open_sftp()
    sftp.get(server_path, local_path)

    # ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command('cd Desktop/ktest-2.0.2/;sudo robot tests/usecases/emobility/cevc/cevc.robot')

    # print(ssh_stdout.read())
    while True:
        line = ssh_stdout.readline()
        if not line:
            break
        print(line)
    ssh.close()
except Exception as e:
    print("服务器%s连接失败")
    print(e)
