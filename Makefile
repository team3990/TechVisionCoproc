.PHONY: setup clean

CFLAGS = -g -Isrc -Izmq/include

# For Raspberry pi
#LDFLAGS = -Lzmq/lib/pi -lzmq -lv4l2 -lopencv_highgui -lopencv_core -lopencv_imgproc -lpthread -lrt 
#For odroid
LDFLAGS = -Lzmq/lib/odroid -lzmq -lv4l2 -lopencv_highgui -lopencv_core -lopencv_imgproc -lpthread -lrt

all: setup VisionCoproc  testcoproc

setup:
	-mkdir obj

VisionCoproc: obj/CommandProcessor.o obj/CameraManager.o obj/DummyCommand.o obj/ImgSaveCommand.o obj/LoggingService.o obj/MessageDispatcher.o obj/OCVCapture.o obj/tinythread.o obj/VisionCommand.o src/VisionCoprocessor.cpp
	g++  ${CFLAGS} obj/CommandProcessor.o obj/CameraManager.o obj/DummyCommand.o obj/ImgSaveCommand.o obj/LoggingService.o obj/MessageDispatcher.o obj/OCVCapture.o obj/tinythread.o obj/VisionCommand.o src/VisionCoprocessor.cpp -o VisionCoproc ${LDFLAGS} 

obj/CommandProcessor.o: src/CommandProcessor.cpp
	g++ -c ${CFLAGS} src/CommandProcessor.cpp -o obj/CommandProcessor.o

obj/CameraManager.o: src/CameraManager.cpp
	g++ -c ${CFLAGS} src/CameraManager.cpp -o obj/CameraManager.o

obj/DummyCommand.o: src/DummyCommand.cpp
	g++ -c ${CFLAGS} src/DummyCommand.cpp -o obj/DummyCommand.o

obj/ImgSaveCommand.o: src/ImgSaveCommand.cpp
	g++ -c ${CFLAGS} src/ImgSaveCommand.cpp -o obj/ImgSaveCommand.o

obj/LoggingService.o: src/LoggingService.cpp
	g++ -c ${CFLAGS} src/LoggingService.cpp -o obj/LoggingService.o

obj/MessageDispatcher.o: src/MessageDispatcher.cpp
	g++ -c ${CFLAGS} src/MessageDispatcher.cpp -o obj/MessageDispatcher.o

obj/OCVCapture.o: src/OCVCapture.cpp
	g++ -c ${CFLAGS} src/OCVCapture.cpp -o obj/OCVCapture.o

obj/tinythread.o: src/tinythread.cpp
	g++ -c ${CFLAGS} src/tinythread.cpp -o obj/tinythread.o

obj/VisionCommand.o: src/VisionCommand.cpp
	g++ -c ${CFLAGS} src/VisionCommand.cpp -o obj/VisionCommand.o

testcoproc:
	g++ ${CFLAGS}  testcoproc.cpp -o testcoproc ${LDFLAGS} 

clean:
	-rm -f obj/*.o
	-rm testcoproc
	-rm VisionCoproc
