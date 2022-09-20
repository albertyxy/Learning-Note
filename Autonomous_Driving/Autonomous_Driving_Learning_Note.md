## Intro to Self-driving Cars

#### **terminology**

**Driving task**

​	perceiving

​	planning

​	controlling

**What makes up a driving task?**

​	lateral control(steering)

​	longitudinal control(braking and accelerating)

​	OEDR(object and event detection and response)

**ODD(operational design domain)**

**taxonomy of driving automation**

L0, L1(Adaptive Cruise Control, Lane Keeping Assistance), L2(require driver's monitoring), L3, L4(High Driving Automation), L5(unlimited ODD)



#### autonomous requirements

perception(identification, understanding motion)

driving decisions and actions

**goals for perception**

​	static objects

​		on road: road and lane-markings, obstructions

​		off road: curbs, traffic lights, road signs

​	dynamic objects

​		vehicles(4 wheelers, 2 wheelers)

​		pedestrians

​	ego localization(GPS, IMU, odometry sensors)

​		position

​		velocity, acceleration

​		orientation, angular motion

**planning approaches**

​	reactive(react only to currently available information)

​	predictive(dependent on trajectory predictions of other agents)

**type of planning**

​	long-term

​	short-term

​	immediate

​	

#### software and hardware

**sensors for perception**

​	**exteroceptive-surroundings**

​		camera

​			comparison metrics: resolution, field of view(FOV), dynamic range

​			stereo camera(depth estimation from synchronized image pairs)

​		lidar

​			comparison metrics: number of beams, points per second, rotation rate, field of view

​		radar

​			comparison metrics: range, field of view, position and speed accuracy

​			WFOV&NFOV

​		ultrasonic, sonar

​			comparison metrics: range, field of view, cost

​	**proprioceptive-internal**

​		GNSS(Global Navigation Satellite System)

​			RTK(real - time kinematic), DGPS(differential GPS), PPP(Precise Point Positioning)

​		IMU(Inertial Measurement Unit)

​		wheel odometry

(camera for appearance input, stereo camera for depth info, lidar for 3D input, radar for object detection, ultrasonic for short-range 3D input, GNSS/IMU/wheel odometry for ego state estimation)

**self-driving computing hardware**

​	GPU(Graphic Processing Unit)

​	FPGA(Field Programmable Gate Array)

​	ASIC(Application Specific Integrated Chip)

​		Nvidia Drive PX

​		Intel & Mobileye EyeQ

​	synchronization hardware

**design hardware configuration---sensor coverage analysis**

highway driving scenario

​	emergency stop, maintain speed, lane change

urban driving scenario

​	emergency stop, maintain speed, lane change, 

​	overtaking, turning or crossing intersections, passing roundabouts

**software stack architecture**

​	environment perception

​		localization

​		dynamic object detection(bounding boxes)-tracking(object tracks)-prediction

​		static object detection

​	environment mapping

​		occupancy grid map

​		localization map

​		detailed road map

​	motion planning

​		mission planner

​		behavior planner

​		local planner

​	controller

​		velocity controller---throttle, brake

​		steering controller---steering angle

​	system supervisor



#### Safety Assurance

**major hazard sources**

mechanical, electrical, hardware, software, sensors, behavioral, fallback, cyber

**NHTSA safety framework**

systems engineering approach to safety

autonomy design

testing & crash mitigation

**safety assessment**

analytical safety

data-driven safety

​	



