CXX=g++
CXXFLAGS=-std=c++11 
#-O3 -mtune=cortex-a8 -mfpu=neon -ftree-vectorize -mapcs -mfloat-abi=hard -funsafe-math-optimizations -Ofast -Wno-pointer-arith
LFLAGS=-I./include/ -lpthread -I./
OBJS=logger.o pid.o

main: $(OBJS) src/main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) src/main.cpp -o main

pid.o: src/pid.cpp include/pid.hpp
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) src/pid.cpp -o pid.o
	
logger.o: lib/src/logger.cpp lib/include/logger.hpp
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) lib/src/logger.cpp -o logger.o
	
clean:
	rm -r -f *.o
	