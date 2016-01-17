project("TechVisionCoprocessor")
cmake_minimum_required(VERSION 2.8.9)
option(WITH_OPENCV "With opencv library" ON)

#Bring the headers, such as Student.h into the project
include_directories(src zmq/include)

file(GLOB SOURCES "src/*.cpp")
link_directories( zmq/lib/ )
set ( PROJECT_LINK_LIBS zmq rt pthread )
find_package( OpenCV )
add_executable(VisionCoproc ${SOURCES})
add_executable(testcoproc testcoproc.cpp)

if (OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
  target_link_libraries (VisionCoproc ${OpenCV_LIBS} v4l2)
  target_link_libraries (testcoproc ${OpenCV_LIBS} v4l2)
  if(WITH_OPENCV)
   add_definitions(-DUSE_OPENCV)
  endif()
endif(OpenCV_FOUND)

target_link_libraries(VisionCoproc ${PROJECT_LINK_LIBS} )
target_link_libraries(testcoproc ${PROJECT_LINK_LIBS} )
