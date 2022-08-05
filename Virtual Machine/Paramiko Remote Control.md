#### To create a virtual machine (e.g. Ubuntu 18.04) using VMware

https://blog.csdn.net/Baiye959/article/details/122886252

**Step1**

install VMware

use VMware Workstation Pro/ VMware Workstation 15 Player

**Step2**

creat a new VM

https://blog.csdn.net/Baiye959/article/details/122886252

not choose “open after creation”

 

**Problems**

1.loading too long at autoinst.iso 

install vm-tools manually

solution: https://blog.csdn.net/Jeff_12138/article/details/121568632

2.black screen when running VM

[https://blog.csdn.net/what_about_us/article/details/81207926?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164485115716781685328817%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=164485115716781685328817&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-81207926.pc_search_result_cache&utm_term=Vmware%20Ubuntu%E9%BB%91%E5%B1%8F&spm=1018.2226.3001.4187](https://blog.csdn.net/what_about_us/article/details/81207926?ops_request_misc=%7B%22request%5Fid%22%3A%22164485115716781685328817%22%2C%22scm%22%3A%2220140713.130102334.pc%5Fall.%22%7D&request_id=164485115716781685328817&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-81207926.pc_search_result_cache&utm_term=Vmware Ubuntu黑屏&spm=1018.2226.3001.4187)

 

**Issues**

1.How can VM share VPN with host

https://zhuanlan.zhihu.com/p/380614384?ivk_sa=1024320u

2.how to change releases in Ubuntu

using aliyun

https://developer.aliyun.com/mirror/ubuntu?spm=a2c6h.13651102.0.0.5a7b1b11txrh0O



#### remote control(eg. in Windows) of VM(requirement: Python2.7.15)

https://blog.csdn.net/qq_29778641/article/details/82186438

https://www.freesion.com/article/9979787216/

https://blog.csdn.net/oJinXuan1/article/details/81034859



This is a guide to use a python script in Windows to control the Ubuntu Terminal which use paramiko based on ssh protocol. The paramiko used below is based on Python 2.7.15, you can update paramiko if you want to use other higher Python version.

The first step is to install the package “paramiko”. To istall paramiko, you should install PyCrypto and ecdsa first. The description below is based on Python 2.7.15, be aware that change the version of package according your Python version. To install PyCrypto, you can just click [pycrypto-2.6.1-amd64_py27.exe](./pycrypto-2.6.1-amd64_py27.exe). Then, to install ecdsa, you should first unzip [python-ecdsa-master.zip](./python-ecdsa-master.zip) and then execute the command “python setup.py install” in the directory. Finally, to install paramiko, it is like the step before, unzip [paramiko-1.7.7.1.zip](./paramiko-1.7.7.1.zip) and then execute “python setup.py install”.



windows访问控制 ubuntu的方式

——通过使用python的paramiko包

可以实现远程访问命令传输，上传、下载文件等

 

```python
import paramiko

\#创建SSH客户端对象

ssh = paramiko.SSHClient()

\#设置访问策略

ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

\#与远程主机进行连接

ssh.connect(hostname = ip,port = port,username = username,password = password)

\#执行命令

ssh.exec_command()
```



 

```bash
在ubuntu中配置ssh

sudo apt-get update

sudo apt-get install openssh-server

查看配置是否成功

sudo ps -e |grep ssh

查看主机的IP地址

ifconfig

sudo service ssh stop 关闭服务：

sudo service ssh restart 重启服务

sudo service ssh status 查看服务状态

netstat –ntl查看接口状态
```



环境：Python2.7.15

需要安装PyCrypto，ecdsa，paramiko

1.安装PyCrypto

双击pycrypto-2.6.1-amd64_py27.exe，正常安装即可，如果之前安装了PyCrypto需要在Python2.7.15\Lib\site-packages下面找到pycrypto，然后uninstall

2.安装ecdsa

解压缩python-ecdsa-master.zip

在解压后目录执行python setup.py install

3.安装paramiko

解压缩paramiko-1.7.7.1.zip，在解压后目录执行

python setup.py build

python setup.py install

 

①如果提示error: Incompatible ssh peer (no acceptable kex algorithm)

错误原因：当前版本paramiko不支持key exchange algorithms

解决方法1：在ubuntu 

sudo gedit /etc/ssh/sshd_config后面添加如下内容

KexAlgorithms diffie-hellman-group-exchange-sha256,diffie-hellman-group14-sha1,diffie-hellman-group-exchange-sha1

解决方法2：更新paramiko到最新版

②如果提示error: Authentication failed.

请检查主机用户名和密码是否正确

