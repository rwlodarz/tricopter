CXX=g++-4.9
CXXFLAGS=-std=c++11 -O3 -mtune=cortex-a8 -mfpu=neon -ftree-vectorize -mapcs -mfloat-abi=hard -funsafe-math-optimizations -Ofast -Wno-pointer-arith
LFLAGS=-I./include/ -lpthread -I./
OBJS=logger.o utils.o i2clib.o ms5611.o mpu9150.o ak8975.o butterfilter.o pwm.o tricopter.o xml.o icl.o motor.o pid.o imufilter.o ocl.o sensor.o

main: $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) main.cpp -o main

logger.o: logger.cc include/logger.h
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) logger.cc -o logger.o
	