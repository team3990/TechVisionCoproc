# TechVisionCoproc
Vision coprocessor

Prerequisites
=============

- g++ 
- cmake 2.8 and higher
- Optionnally, opencv and video4linux
- The comm library zmq is in the subdir zmq. Default builds for RaspberryPi, Odroid and roboRio2016 are supplied. If you don't find your favorite platform, you will have to build libzmq yourself (and getting the c++ binding)


Installation
============

Move to the working directory. Copy the appropriate libzmq.a library located in zmq/lib/* to zmq/lib, e.g.:
> cp zmq/lib/odroid/libzmq.a zmq/lib

Then, the following series of commands will build the server and a test tool.

> mkdir build
> cd build
> cmake ..
> make

If everything went well, two binaries should be created: 
- the coprocessor server: VisionCoproc
- a test utility: testcoproc

Execution
=========

Launching VisionCoproc from the shell, we should get:

> ./VisionCoproc
  Hit Ctrl-C to quit
  Listening

If you open up another shell and cd to the build directory, you can use the test tool to verify that communication is ok:

> ./testcoproc status

  Command processor status:
  Version 2016
  Image dump location: /media/data/images
   No job running
  Camera manager: No camera support (opencv not used)


Communication
=============

Commands handled by the coprocessor so far:

reset				: stops processing, destroys results
status				: returns internal status 
saveimg				: captures an image from camera and dumps it to disk   
test				: executes a fake command 
r_test				: sends back "Test mode 1: result=pi"
r_saveimg            		: sends back filename of saved image from cam or "Trying to save empty image!" if no camera is connected.


* Sending a command always initiates a response. Typical use:  roboRio sends "test", waits a bit and sends "r_test" to get the result.
* More than one command can be processed at the same time, but they have to be different.
* If a command such as "test" is sent twice in a row, the first response is "Started" (which is ok) but the second one is "Busy".
* If a command such as "test" is sent but the next command "r_test" is sent too early (before the end of the detection), the response is "Still thinking".
* Following a bad command, the response is "Unknown command".
* Following a reset, the response is "Done".

