#compile file
comp-%: %.cpp
	clear
	g++ -std=c++14 $*.cpp `pkg-config --libs --cflags opencv` -o _$*
comp-camera_cal: camera_calibration/camera_calibration.cpp
	clear
	g++ -std=c++14 camera_calibration/camera_calibration.cpp `pkg-config --libs --cflags opencv` -o camera_calibration/_camera_calibration

#req1
run-req1: comp-main
	./_main 1 red_eyes.jpg
run-req1-%: comp-main
	./_main 1 $*

#req2
run-req2: comp-main
	./_main 2

#req3
run-req3: comp-main
	./_main 3
