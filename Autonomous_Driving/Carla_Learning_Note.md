## Carla (Car Learning to Act)

#### Intro

open-source autonomous driving simulator

client-server architecture

API in python and C++

UE4

OpenDRIVE standard 1.4

used for autonomous driving R&D(Research and Development)



#### World and Client

create a Client

```python
client = carla.Client('localhost', 2000)
client.set_timeout(10.0)
```

connect World

```python
world = client.get_world()p
world = client.load_world('Town01')
```

weather

```python
carla.WeatherParameters(…)
world.set_weather(carla.WeatherParameters.WetCloudySunset)
```



### Blueprint and Actor

Actors: vehicles, walkers, sensors, traffic signs, traffic lights, and the spectator

blueprint library (https://carla.readthedocs.io/en/0.9.12/bp_library/)

```python
blueprint_library = world.get_blueprint_library()
```

find a specific blueprint

```python
bp = blueprint_library.find('sensor.other.collision')
bp = random.choice(blueprint_library.filter('vehicle.*.*'))
bp = blueprint_library.filter("model3")[0]
```

create an actor

```python
transform = Transform(Location(x=230, y=195, z=40), Rotation(yaw=180))
actor = world.spawn_actor(blueprint, transform)
#spawn a random vehicle
spawn_point = random.choice(world.get_map().get_spawn_points())
vehicle = world.spawn_actor(bp,spawn_point)

#spawn a random walker
spawn_point = carla.Transform()
spawn_point.location = world.get_random_location_from_navigation()
```

##### Vehicle

```python
vehicle.set_autopilot(True)
vehicle.apply_control(carla.VehicleControl(throttle=1.0, steer=-1.0))
```

carla.VehiclePhysicsControl 

carla.BoundingBox



##### Sensor

Sensors: Cameras (RGB, depth and semantic segmentation), Collision detector, Gnss sensor, IMU sensor, Lidar raycast, Lane invasion detector, Obstacle detector, Radar, RSS (Responsibility Sensitive Safety).

e.g. Camera

```python
camera_bp = blueprint_library.find('sensor.camera.depth')
camera_bp = blueprint_library.find('sensor.camera,rgb')
camera_transform = carla.Transform(carla.Location(x=1.5, z=2.4))
camera = world.spawn_actor(camera_bp, camera_transform, attach_to=vehicle)
#sensors listen to data
camera.listen(lambda image: image.save_to_disk('output/%06d.png' % image.frame))
```







### commands, applied in batches

```python
client.apply_batch([carla.command.DestroyActor(x) for x in actor_list])
```



### [import map in CARLA](./Carla.pptx)

**input .xodr directly**

```bash
python3 config.py -x opendrive/TownBig.xodr
client.generate_opendrive_world()
```



**Carla package**

use Docker

system requirements:

(64-bit version of Docker in Ubuntu 16.04+, Minimum 8GB of RAM, Minimum 700 GB available disk space for building container images, Git version control)

```python
python3 docker_tools.py --input ~/path_to_input_folder --output ~/path_to_output_folder --packages map_package
./ImportAssets.sh
```

open Carla package

```python
python3 config.py --map <mapName>
```



**Carla source build**

move .fbx, .xodr, .json to Import Folder

```python
make import/make import  ARGS="--package=<package_name>"
```

open Carla Source and load level(carla\Unreal\CarlaUE4\Content\package_name)

use Carla exporter to export .obj file (carla\Unreal\CarlaUE4\Saved)

move .obj and .xodr to carla\Util\DockerUtils\dist

```python
#Generate pedestrian navigation
./build.sh map_name 
```

move .bin to carla\Unreal\CarlaUE4\Content\Package_name\Nav



### **[Carla-ROS-Bridge](./Carla.pptx)**

install ROS bridge(build from source)

```bash
mkdir -p ~/carla-ros-bridge/catkin_ws/src
cd ~/carla-ros-bridge
git clone https://github.com/carla-simulator/ros-bridge.git
cd ros-bridge
git submodule update --init
cd ../catkin_ws/src
ln -s ../../ros-bridge
source /opt/ros/melodic/setup.bash # Watch out, this sets ROS Kinetic 
cd ..
rosdep update
rosdep install --from-paths src --ignore-src -r
catkin_make
```

edit ~/.bashrc

```bash
source /opt/ros/melodic/setup.bash
export PYTHONPATH=$PYTHONPATH:<path/to/carla/>/PythonAPI/carla/dist/carla-0.9.11-py2.7-linux-x86_64.egg
export PYTHONPATH=$PYTHONPATH:<path/to/carla/>/PythonAPI/carla
export SCENARIO_RUNNER_PATH=<path/to/scenario_runner/>
```

every time to start ROS-bridge

```bash
source ~/carla-ros-bridge/catkin_ws/devel/setup.bash
```

have a test

```bash
roslaunch carla_ros_bridge carla_ros_bridge.launch
roslaunch carla_ros_bridge carla_ros_bridge_with_example_ego_vehicle.launch
roslaunch carla_ad_demo carla_ad_demo.launch
```

ROS Packages(related to ROS-Bridge)

```python
carla_ackermann_control 
carla_spawn_objects 
carla_ackermann_msgs
carla_twist_to_control
carla_ad_agent 
carla_walker_agent 
carla_ad_demo
carla_waypoint_publisher
pcl_recorder
carla_common
carla_waypoint_types
carla_manual_control
ros_compatibility
carla_ros_bridge
rqt_carla_control
carla_ros_scenario_runner
rviz_carla_plugin
carla_ros_scenario_runner_types
```



### Scenario Runner

### [(carla-scenariorunner.readthedocs.io)](https://carla-scenariorunner.readthedocs.io/en/latest/)

**three ways to run scenarios**

1.Scenarios by themselves

```bash
python scenario_runner.py --scenario <ScenarioName>
#run all scenarios of one scenario class
python scenario_runner.py --scenario group:FollowLeadingVehicle
```

2.Scenarios based on routes

```bash
python scenario_runner.py --route <path/to/route-file> <path/to/scenario_sample_file> [route id] --agent <path/to/agent_file>
```

3.using OpenSCENARIO

```bash
python scenario_runner.py --openscenario <path/to/xosc-file>
```

[**list of supported scenarios**](https://carla-scenariorunner.readthedocs.io/en/latest/list_of_scenarios/)

```python
FollowLeadingVehicle
FollowLeadingVehicleWithObstacle
VehicleTurningRight
VehicleTurningLeft
OppositeVehicleRunningRedLight
StationaryObjectCrossing
DynamicObjectCrossing
NoSignalJunctionCrossing
ControlLoss
ManeuverOppositeDirection
OtherLeadingVehicle
SignalizedJunctionRightTurn
SignalizedJunctionLeftTurn
```

##### test cases

1.control loss

2.lane change

3.obstacle detection

4.handling intersections

**create a new scenario**

1.Initialize Method

2.CreateBehavior method

3.CreateTestCriteria method

```python
class NewScenario(BasicScenario): 
 # some ego vehicle parameters
 # some parameters for the other vehicles

   def __init__(self, world, ego_vehicles, config, randomize=False, debug_mode=False, criteria_enable=True, timeout=60):
       """
       Initialize all parameters required for NewScenario
       """

       # Call constructor of BasicScenario
       super(NewScenario, self).__init__(
         "NewScenario",
         ego_vehicles,
         config,
         world,
         debug_mode,
         criteria_enable=criteria_enable)
   def _create_behavior(self):
       """
       Setup the behavior for NewScenario
       """
   def _create_test_criteria(self):
       """
       Setup the evaluation criteria for NewScenario
       """
```

**test scenarios with custom map**

modify scenario configuration(xml)

```xml
<?xml version="1.0"?>
<scenarios>
    <!-- scenario name MUST contain 'left' or 'right', defines whether car comes from left or right lane-->
    <scenario name="CutInFrom_left_Lane" type="CutIn" town="Lingang">
        <ego_vehicle x="-391.6" y="-420.7" z="4" yaw="270" model="vehicle.lincoln.mkz2017" />
	    <other_actor x="-373.4" y="-381.5" z="-100" yaw="270" model="vehicle.tesla.model3" />
        <weather cloudiness="0" precipitation="0" precipitation_deposits="0" wind_intensity="0" sun_azimuth_angle="0" sun_altitude_angle="75" />
    </scenario>
    <scenario name="CutInFrom_right_Lane" type="CutIn" town="Lingang">
        <ego_vehicle x="-391.6" y="-420.7" z="4" yaw="270" model="vehicle.lincoln.mkz2017" />
	    <other_actor x="-349.4" y="-321.5" z="-100" yaw="270" model="vehicle.tesla.model3" />
        <weather cloudiness="0" precipitation="0" precipitation_deposits="0" wind_intensity="0" sun_azimuth_angle="0" sun_altitude_angle="75" />
    </scenario>
</scenarios>
```



**py-trees**---decision making engine

Composites and Child structure:

Composites: Sequences and Parallels(factories), Selectors(decision makers)

​	Selector: select a child to execute based on cascading priorities

​	Sequence: execute children concurrently

​	Parallel: execute children sequentially

​		policy: SuccessOnOne /  SuccessOnAll

Status: Success, Running, Failure



atomic behavior(atomic_behaviors.py)

```python
class WaypointFollower(AtomicBehavior):
```

This is an atomic behavior to follow waypoints while maintaining a given speed. If no plan is provided, the actor will follow its forward waypoints. If no target velocity is provided, the actor continues with its current velocity.

```python
class LaneChange(WaypointFollower):
```

**Important parameters:**

actor: CARLA actor to execute the behavior

speed: speed of the actor for the lane change, in m/s

direction: 'right' or 'left', depending on which lane to change

distance_same_lane: straight distance before lane change, in m

distance_other_lane: straight distance after lane change, in m

distance_lane_change: straight distance for the lane change itself, in m



edit parameters

```python
#lane change from right on straight road
ego_vehicle x="-386.4" y="-406.4" z="4" yaw="250" 
other_actor x="-365.4" y="-359.5" z="-100" yaw="250" 
distance_same_lane=5(5)
distance_other_lane=100(300)
lane_changes=1(1) --->0.5
#lane change from left on curve road
ego_vehicle x="-169.8" y="233.8" z="4" yaw="285"
other_actor x="-185.3" y="262.5" z="-100" yaw="310"
self._delta_velocity = 20(10)
self._trigger_distance = 10(30)
endcondition.DriveDistance = 50(200)
distance_same_lane=5(5)
distance_other_lane=50(300)
lane_changes=1(1)--->1.5
```

add a new tag in xml file

```python
#lane_changes as an example
#scenario_parser.py line 73
new_config.lane_changes = scenario.attrib.get('lane_changes', 1.0)
#cut_in.py line 56
self._lane_changes = config.lane_changes
#cut_in.py line 127, line 131
lane_change = LaneChange(self.other_actors[0], speed=None, direction='right', distance_same_lane=5, distance_other_lane=50, lane_changes=float(self._lane_changes))
```



### **ASAM** **OpenSCENARIO**

Association for Standardization of Automation and Measuring systems(ASAM)

ASAM OpenDRIVE(road network descriptions) and ASAM OpenCRG(road surface profiles)

#### **Introduction**

to describe complex, synchronized maneuvers that involve multiple entities like vehicles, pedestrians and other traffic participants

Maneuvers, actions, trajectories and other elements can be organized in catalogs and can be parameterized, which allows test automation

The format is technology and vendor independent

**two versions---V1.x, V2.0.0** 

- V1.x is a low-level and concrete specification format, primarily designed to be read by simulation tools.
- V2.0.0 allows those users that create maneuver descriptions and tests to define scenarios at a higher level of abstraction as well as providing alternative expression methods to the current XML format of OpenSCENARIO 1.0.0 via a domain-specific language (DSL).

use XSLT migration script to transform 0.9.1 to 1.0.0

```bash
xsltproc -o newScenario.xosc migration0_9_1to1_0.xslt oldScenario.xosc
```

#### **Concepts**

Entity---Vehicles and Pedestrians

Storyboard---story, act, maneuver group, maneuver, event, action

Condition

Catalog, ParameterDeclaration

**general concepts**

Units(SI)

definition of date and time e.g. （CET）2011-03-10 11:23:56

```xml
2011-03-10T11:23:56.000+0100
```

Naming

Road Networks and Environment Models

Controllers

Routes

Trajectories---Polyline, Clothoid, Nurbs

Coordinate Systems: right handed coordinate system(ISO 8855:2011), road based coordinate system(s-t)

Positioning

- Absolute/relative in the world coordinate system
- Relative to another Entity
- Absolute/relative in the road coordinate system
- Absolute/relative in the lane coordinate system
- Relative to a Route

Traffic Simulation 

**Storyboard**

Storyboard--- Init + Story

Init: initial conditions for the scenario, e.g. position and speed

Story

​	    Act (consist of Actions): "when" something happens in the timeline of a corresponding Story

​		startTriggers and stopTriggers

​		ManeuverGroup: "who" is doing something in the scenario

​		Maneuvers: "what" is happening in a scenario

**Entity**

Vehicles or Pedestrians or MiscObjects(listed as follows)

- none
- obstacle
- pole
- tree
- vegetation
- barrier
- building
- parkingSpace
- patch
- railing
- trafficIsland
- crosswalk
- streetLamp
- gantry
- soundBarrier 
- wind
- roadMark

Entity & EntitySelection---EntityRef

**Actions**

​	**Private Action**(assigned to instances of Entity)

​		LongitudinalAction

​		LateralAction

​		VisibilityAction

​		SynchronizeAction

​		ActivateControllerAction

​		ControllerAction

​		TeleportAction

​		RoutingAction

​			AssignRouteAction: Using Waypoints on the road network and a RouteStrategy

​			FollowTrajectoryAction: Using vertices, timings and a corresponding interpolation strategy

​			AcquirePositionAction: shortest Route from current to target  position along the road network

​	**Global Action**(modify non-entity related quantities)

​		EnvironmentAction

​		EntityAction

​		ParameterAction

​		InfrastructureAction

​		TrafficAction

​	**User Defined Action**( customized Action)

​		Conflicting Action

**Events**

Acts-Events-Maneuver

Priority: overwrite, skip, parallel

**Catalog**

eight different kinds of elements that can be outsourced to a Catalog:

Vehicle, Pedestrian, MiscObject, Controllers, Trajectory, Route, descriptions of Environment and Maneuvers

ParameterDeclaration, CatalogReference(catalogName and entryName), ParameterAssignment

**Conditions and Triggers**

Condition-ConditionGroup-Trigger

startTrigger and stopTrigger

Condition Type: name, delay, and conditionEdge(rising, falling, or risingOrFalling)

ByEntityCondition, ByValueCondition

**States and Transitions of StoryboardElement** 

States: Standby, Running, and Complete

Transitions: Start, End, Stop, Skip

#### **Scenario Creation**

Description:  The Ego vehicle is driving along an urban road approaching a junction on the offside. It is being followed by two influencing vehicles, c1 and c2 (the movements of which are controlled by the scenario). A third influencing vehicle (c3) is waiting to turn right at the junction. As The Ego vehicle (Ego) approaches the junction, c1 and c2 start to overtake. Slightly later, c3 starts to turn right, which prompts c1 and c2 to make an emergency stop.

```xml
<!--Init Section-->
<Storyboard>
    <Init>
        <Actions>
            <Private entityRef = "Ego">
                <PrivateAction>
                    <!-- Set Ego to its initial position -->
                    <TeleportAction>
                        <Position>
                            <WorldPosition x = "-2.51"
                                           y = "-115.75"
                                           z = "0"
                                           h = "1.57"
                                           p = "0"
                                           r = "0" />
                        </Position>
                    </TeleportAction>
                </PrivateAction>
                ...
                <!-- Similar actions -->
            </Private>
        </Actions>
   </Init>
    ...
</Storyboard>

<!--Stories-->
<Story name     = "AbortedOvertake">
    <Act name   = "AbortedOvertakeAct1">
        ...
        <!-- Act content describing overtakes -->
    </Act>
    <Act name   = "AbortedOvertakeAct2">
        ...
        <!-- Act content describing emergency stops -->
    </Act>
</Story>
<Story name = "RightTurn">
    <Act name   = "RightTurnAct">
        ...
        <!-- Act content describing right turn -->
    </Act>
</Story>

<!--Acts-->
<Act name = "RightTurnAct">
    <!-- Maneuver Group -->
    ...
    <StartTrigger>
        <ConditionGroup>
            <Condition
                name    = "EgoCloseToJunction"
                delay   = "0"
                conditionEdge   = "rising">
                <!-- ByEntity condition: Ego close to junction -->
                ...
            </Condition>
        </ConditionGroup>
    </StartTrigger>
</Act>

<!--ManeuverGroup-->
<ManeuverGroup name                  = "c1ManeuverGroup"
               maximumExecutionCount = "1">
    <Actors    selectTriggeringEntities = "false">
        <EntityRef entityRef    = "c1"/>
    </Actors>
    <CatalogReference catalogName   = "overtake"
                       entryName     = "Overtake Ego vehicle">
        <!—Parameter assignment -->
        ...
    </CatalogReference>
</ManeuverGroup>

<ManeuverGroup name                  = "c2ManeuverGroup"
               numberOfExecutions    = "1">
    ...
            <!-- similar to above -->
</ManeuverGroup>

<!--Maneuver-->
<Catalog name = "Overtake">
    <Maneuver name = "Overtake Ego Vehicle">
        <ParameterDeclarations>
            <ParameterDeclaration name = " $OvertakingVehicle"
                                  parameterType = " string"
                                  value = ""/>
            <!-- "" will be overwritten by scenario -->
        </ParameterDeclarations>
        <!-- Events to define overtake behaviour -->
        <Event > ... </Event>
        ...
    </Maneuver>
</Catalog>
<ManeuverGroup  name    = "c1ManeuverGroup"
                maximumExecutionCount   = "1">
    <Actors  selectTriggeringEntities    = "false">
        <EntityRef  entityRef   =   "c1"/>
    </Actors>
    <CatalogReference   catalogName     = "Overtake"
                        entryName   = "OvertakeEgoVehicle">
        <ParameterAssignments>
            <ParameterAssignment parameterRef  = "OvertakingVehicle"
                          		 value = "c1"/>
        </ParameterAssignments>
    </CatalogReference>
</ManeuverGroup>

<ManeuverGroup  name    = "c2ManeuverGroup"
                maximumExecutionCount   = "1">
    <Actors     selectTriggeringEntities    = "false">
        <EntityRef  entityRef   = "c2"/>
    </Actors>
    <CatalogReference   catalogName = "Overtake"
                        entryName   = "OvertakeEgoVehicle">
        <ParameterAssignments>
            <ParameterAssignment parameterRef  = "OvertakingVehicle"
                            value = "c2"/>
        </ParameterAssignments>
    </CatalogReference>
</ManeuverGroup>

<!--Event-->
<Event  name    = "brake event"
    priority    = "overwrite">
    ...
    <!-- Emergency stop action -->
    <StartTrigger>
        <ConditionGroup>
            <Condition  name = "StartConditionOfAbortedOvertakeAct2"
                        delay = "0"
                        conditionEdge = "none">
                <ByValueCondition>
                    <SimulationTimeCondition value = "0"
                                             rule  = "greaterThan"/>
                </ByValueCondition>
            </Condition>
        </ConditionGroup>
    </StartTrigger>
</Event>
```

**Examples:**

Cut-In, Slow Preceding Vehicle, End of Traffic Jam, End of Traffic Jam Neighboring Lane Occupied, Double Lane Changer, Fast Overtake with Re-Initialization, Overtaker, Traffic Jam, Synchronized Arrival at Intersection



### scenariogeneration

python package

```bash
pip install scenariogeneration
```

**sub-modules**

scenariogeneration . esmini_runner

scenariogeneration . helpers

scenariogeneration . scenario_generator

scenariogeneration . xodr

scenariogeneration . xosc

**xosc**

V1.0.0 and V1.1.0 of OpenSCENARIO
