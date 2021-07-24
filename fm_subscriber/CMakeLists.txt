cmake_minimum_required(VERSION 2.8.3)
project(fm_subscriber)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
	roscpp
	message_generation
	std_msgs
	cv_bridge
	image_transport
	sensor_msgs
)

add_message_files(FILES MsgAuroraStatus.msg)
generate_messages(DEPENDENCIES std_msgs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

#add_service_files(FILES SrvTutorial.srv)
#add_message_files(FILES MsgTutorial.msg)
#generate_messages(DEPENDENCIES stdore_msgs)

QT5_WRAP_UI(myUIC
        ui/mainwindow.ui
)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#	INCLUDE_DIRS include
#       LIBRARIES fm_subscriber
	CATKIN_DEPENDS roscpp std_msgs message_runtime
#	DEPENDS system_lib
)

###########
## Build ##
###########

link_directories(/usr/lib)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}/..
	${OpenCV_INCLUDE_DIRS}
	/usr/include/yaml-cpp
)


## Declare a C++ executable
add_executable(${PROJECT_NAME}_node
	src/main.cpp
	src/mainwindow.cpp
	src/mainwindow.hpp
	src/qros.cpp
	src/qros.hpp
	src/qrobot.cpp
	src/qrobot.hpp
	ui/mainwindow.ui
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 1.png
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 2.png
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 3.png
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 4.png
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 5.png
#	src/img/Battery\ Icons\ -\ Colorful\ 128px\ 6.png
)

qt5_use_modules(fm_subscriber_node Widgets SerialPort)

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${OpenCV_LIBS} yaml-cpp)

