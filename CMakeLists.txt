cmake_minimum_required(VERSION 2.8.3)
project(omnibot_ros_teleop)
find_package(catkin REQUIRED roscpp geometry_msgs)
find_package(SDL REQUIRED sdl2)

catkin_package()

link_directories(/usr/local/lib)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${SDL_INCLUDE_DIRS}
)

add_executable(joystick_drive src/joystick_drive.cpp)
target_link_libraries(joystick_drive ${catkin_LIBRARIES} ${SDL_LIBRARIES})
