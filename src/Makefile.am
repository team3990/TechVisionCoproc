AUTOMAKE_OPTIONS = foreign

CXXFLAGS = -I. -I../zmq/include 
LDFLAGS= -Lzmq/lib/odroid -lzmq 

#if nv_opencv
CXXFLAGS += -I/usr/include
LDFLAGS += -lopencv_highgui -lopencv_core -lopencv_imgproc -lv4l2
#endif

LDFLAGS += -lpthread -lrt

bin_PROGRAMS = VisionCoproc testcoproc

VisionCoproc_SOURCES = CommandProcessor.cpp CameraManager.cpp DummyCommand.cpp ImgSaveCommand.cpp LoggingService.cpp MessageDispatcher.cpp tinythread.cpp VisionCommand.cpp VisionCoprocessor.cpp

VisionCoproc_SOURCES += OCVCapture.cpp

testcoproc_SOURCES = testcoproc.cpp

