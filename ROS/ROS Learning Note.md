reference links

https://wiki.ros.org/ROS/Tutorials

https://blog.csdn.net/sinat_26057343/article/details/119967089

https://blog.csdn.net/wanghq2013/article/details/123261772

https://blog.csdn.net/lhb0709/article/details/122910807



**install ROS**

Kinetic——Ubuntu 16.04

Melodic——Ubuntu18.04

install ROS Melodic for Ubuntu18.04

https://blog.csdn.net/kik9973/article/details/118755045

install ROS in windows

https://www.bilibili.com/video/av839826705/



sudo apt update

sudo apt install ros-melodic-desktop-full

sudo rosdep init

sudo rosdep update

echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc

source ~/.bashrc

**make a test**

roscore #to start ROS Master

rosrun turtlesim turtlesim_node

rosrun turtlesim turtle_teleop_key

rqt_graph #look up the relationship between node



**set up a workspace**

mkdir -p ~/catkin_ws/src

cd ~/catkin_ws/src

catkin_init_workspace

cd ~/catkin_ws

catkin_make

source devel/setup.bash



echo $ROS_PACKAGE_PATH

recommended: echo "source ~/catkin_ws/devel/setup.sh" >> ~/.bashrc



cd ~/catkin_ws/src

catkin_creat_package name dependency

catkin_create_pkg name std_msgs rospy roscpp



1.src：代码空间（source space） //放功能包的源码

2.build：编译空间（build space） //编译过程中中间文件（二进制） 所以几乎用不到

3.devel：开发空间（development space） ros2仅保留install //里面放置开发中可执行文件和库

4.install：安装空间（install space） //存放编译成功后的可执行文件

创建与开发需要关注src、devel两空间

ROS用节点（Node）的概念表示一个应用程序，不同node之间通过事先定义好格式的话题（Topic），服务（Service），动作（Action）来实现连接。



**ROS Package** 

(Packages are the software organization unit of ROS code)

rospack find [package_name]

rospack find roscpp

roscd roscpp

rosls roscpp

**package dependencies**

rospack depends1 beginner_tutorials #First-order dependencies

rospack depends1 rospy

rospack depends beginner_tutorials #Indirect dependencies

Customizing the package.xml

 

\#install a ros package

sudo apt-get install ros-melodic-ros-tutorials

 

**roscore, rosnode, rosrun**

roscore #start rosmaster

rosrun #allows you to use the package name to directly run a node within a package (without having to know the package path)

rosrun [package_name] [node_name]

rosnode list

rosnode ping [node_name]

rosnode info [node_name]

 



**rostopic**

rostopic –h

rostopic list

rostopic list --verbose

**Messages**

rostopic type [topic]

rosmsg show [rostopic type]

rostopic type [topic] | rosmsg show

 

publish messages to a given topic

rostopic pub [topic] [msg_type] [args]

\#only publish one message then exit

rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'

\#define 1Hz, publish a steady stream of commands

rostopic pub /turtle1/cmd_vel geometry_msgs/Twist -r 1 -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, -1.8]'

 

rostopic hz [topic]

rostopic echo [topic]

rqt_graph #creates a dynamic graph of what's going on in the system. 

rqt_plot #displays a scrolling time plot of the data published on topics

(rqt_graph and rqt_plot are both parts of the rqt package)

 

**ROS services**

(Services are another way that nodes can communicate with each other. Services allow nodes to send a request and receive a response)

rosservice list

rosservice type [service]

rosservice type [service] | rossrv show

rosservice call [service] [args]

 

**Parameters**

(rosparam allows you to store and manipulate data on the ROS [Parameter Server](https://wiki.ros.org/Parameter Server). The Parameter Server can store integers, floats, boolean, dictionaries, and lists. rosparam uses the YAML markup language for syntax)

rosparam –h

rosparam list

rosparam set [param_name]

rosparam get [param_name]

 

**rqt_console and rqt_logger_level**

for debugging

rqt_console attaches to ROS's logging framework to display output from nodes. rqt_logger_level allows us to change the verbosity level (DEBUG, WARN, INFO, and ERROR) of nodes as they run

**roslaunch**

roslaunch starts nodes as defined in a launch file.

roslaunch [package] [filename.launch]

the Launch File(.launch)



**msg and srv**

msg files are simple text files that describe the fields of a ROS message

an srv file describes a service——a request and a response(the two parts are separated by '---' line)

**use msg**

msg/*.msg

https://wiki.ros.org/action/show/msg?action=show&redirect=ROS%2FMessage_Description_Language

**in package.xml**

<build_depend>message_generation</build_depend>

<exec_depend>message_runtime</exec_depend>**CMakeLists.txt**

find_package(…message_generation)

catkin_package(CATKIN_DEPENDS message_runtime)

add_message_files() √

generate_messages()

 

**use srv**

srv/*.srv

**in package.xml**

<build_depend>message_generation</build_depend>

<exec_depend>message_runtime</exec_depend>

**CMakeLists.txt**

find_package(…message_generation)

catkin_package(CATKIN_DEPENDS message_runtime)

add_service_files() √

generate_messages()

 

at build time, we need "message_generation", while at runtime, we only need "message_runtime"

message_generation works for both msg and srv

 

 

**write a publisher and subscriber node in C++(/src), in python(/Scripts)**

.cpp/.py

modify CMakeLists.txt

 

**Writing the publisher Node (src/talker.cpp)**

1.Initialize the ROS system

2.Advertise that we are going to be publishing std_msgs/String messages on the chatter topic to the master

3.Loop while publishing messages to chatter 10 times a second

**Writing the Subscriber Node(src/listener.cpp)**

1.Initialize the ROS system

2.Subscribe to the chatter topic

3.Spin, waiting for messages to arrive

4.When a message arrives, the chatterCallback() function is called

 

 

**write a service and client node in C++(/src), in python(/Scripts)**

.cpp/.py

modify CMakeLists.txt

 

**make a text**

rosrun beginner_tutorials add_two_ints_server   (C++)

rosrun beginner_tutorials add_two_ints_server.py (Python)

$ rosrun beginner_tutorials add_two_ints_client 1 3   (C++)

$ rosrun beginner_tutorials add_two_ints_client.py 1 3 (Python)

 

 

**rosbag**

mkdir ~/bagfiles

cd ~/bagfiles

rosbag record -a

rosbag info <your bagfile>

rosbag play <your bagfile>

\#only record the particular topics to a bag file named subset.bag

rosbag record -O subset /turtle1/cmd_vel /turtle1/pose

 

**read/extract messages from the bag file**

rosbag info mybag.bag | grep -E "(topic1|topic2|topic3)"

rostopic echo /obs1/gps/fix | tee topic1.yaml

rosbag play --immediate demo.bag --topics /obs1/gps/fix /diagnostics_agg

use ros_readbagfile

 

 

**ROS NetworkSetup****(Running ROS across multiple machines)**

ping with each other via IP

set ROS Mater Path

export ROS_MASTER_URI=http://192.168.209.129:11311 每一个新的终端都要重新export

sudo gedit /etc/hosts

192.168.209.129 hostname

 

**make a test**

roscore

rosrun turtlesim turtlesim_node

 

rostopic pub /chatter std_msgs/String "hello" -r1

rostopic echo /chatter

 

 

**custumize Message**

**default msg**

https://wiki.ros.org/action/show/msg?action=show&redirect=ROS%2FMessage_Description_Language

https://www.youtube.com/watch?v=F3zyAV4alCs

string data

int32 counter

 

make a custom .msg

​	edit CMakelist

​	add_message_files()

​	catkin_install_python()

set up a publisher node and subscriber node

​     msg_to_publish=custom()





**ROSserial**

rosserial_embeddedlinux

http://wiki.ros.org/rosserial_embeddedlinux

steps to set up the build environment for your embedded linux system

1. Install the rosserial stack on your ros workstation (the Ubuntu system where you build and run ROS software).

2. Build the rosserial_embeddedlinux package. This creates the libraries and examples directories.

3. Copy the libraries and examples directories to your embedded linux development environment (which may be on your ros workstation or elsewhere: e.g. a Windows PC).

4. Configure your embedded linux development environment by adding the libraries/ros_lib directory to the #include search path

5. Build an embedded linux application that uses ros interfaces (usually with a cross-compiler - see your development environment documentation)

6. Download the application to the target embedded linux system and test/debug.

Bugs

1.Service client on the embedded system doesn't work reliably. (Publisher, Subscriber, and Service server are good.) This is true on both arduino and embedded linux packages.

2.Parameters are not supported on the embedded system.

3.APIs are not thread-safe



