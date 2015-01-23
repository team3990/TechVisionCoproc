# TechVisionCoproc
Code vision sur Odroid

Communication
=============

Commands handled by the coprocessor so far:

reset					: stops processing, destroys results
status					: returns internal status 
saveimg1				: captures an image from camera1 and dumps it to disk   TODO
saveimg2				: idem, for camera 2   TODO
detectyote			: detects a yellow tote   TODO
detectplatform		: detects the location of the scoring platform  TODO
test					: executes a fake command that should last 50ms
longtest				: executes a fake command that should last 2s
r_detectyote			: sends back the results from the yellow tote detector
r_detectplatform		: sends back the results from thescoring platform detector
r_test					: sends back "Test mode 1: result=pi"
r_longtest				: sends back "Test mode 2: result=nan"


* Sending a command always initiates a response. Typical use:  roboRio sends "detectyote", waits a bit and sends "r_detectyote" to get the result.
* More than one command can be processed at the same time, but they have to be different.
* If a command such as "detectyote" is sent twice in a row, the first response is "Started" (which is ok) but the second one is "Busy".
* If a command such as "detectyote" is sent but the next command "r_detectyote" is sent too early (before the end of the detection), the response is "Still thinking".
* Following a bad command, the response is "Unknown command".
* Following a reset, the response is "Done".

