# cmake needs this line
cmake_minimum_required(VERSION 3.1.0)

# Define project name
project(take_a_photo)

# Enable C++11
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
        roscpp
        cv_bridge
        sensor_msgs
        std_msgs
        )

# Find librealsense2 installed package
find_package(realsense2 REQUIRED)

# OpenCV
set(OpenCV_DIR "/home/user/opencv/build")
#option( OpenCV_STATIC OFF )
find_package(OpenCV REQUIRED)
#include_directories( ${OpenCV_INCLUDE_DIRS} )
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()


# Add includes
#include_directories( ${CMAKE_CURRENT_LIST_DIR} )
include_directories(
        include
        ${realsense2_INCLUDE_DIR}
        ${catkin_INCLUDE_DIRS}
)

catkin_package(
        LIBRARIES ${PROJECT_NAME}_pub
        CATKIN_DEPENDS message_runtime roscpp sensor_msgs std_msgs
        cv_bridge
)

catkin_package(
        LIBRARIES ${PROJECT_NAME}_sub
        CATKIN_DEPENDS message_runtime roscpp sensor_msgs std_msgs
        cv_bridge
)


# Declare the executable target built from your sources
add_executable(
        ${PROJECT_NAME}_pub
        src/image_publisher.cpp
)

# Link your application with some libraries
target_link_libraries(
        ${PROJECT_NAME}_pub
        ${catkin_LIBRARIES}
        ${realsense2_LIBRARY}
        ${OpenCV_LIBS}
)

# Declare the executable target built from your sources
add_executable(
        ${PROJECT_NAME}_sub
        src/image_subscriber.cpp

)

# Link your application with some libraries
target_link_libraries(
        ${PROJECT_NAME}_sub
        ${catkin_LIBRARIES}
        ${realsense2_LIBRARY}
        ${OpenCV_LIBS}
)