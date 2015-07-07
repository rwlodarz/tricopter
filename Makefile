CXX=g++
CXXFLAGS=-std=c++11 
#-O3 -mtune=cortex-a8 -mfpu=neon -ftree-vectorize -mapcs -mfloat-abi=hard -funsafe-math-optimizations -Ofast -Wno-pointer-arith
LFLAGS=-I./include/ -lpthread -I./
OBJS=logger.o

main: $(OBJS) src/main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) src/main.cpp -o main

logger.o: src/lib/logger.cc include/lib/logger.h
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) logger.cc -o logger.o
	