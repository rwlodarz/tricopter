CXX=g++
CXXFLAGS=-std=c++11 -static-libstdc++
#-O3 -mtune=cortex-a8 -mfpu=neon -ftree-vectorize -mapcs -mfloat-abi=hard -funsafe-math-optimizations -Ofast -Wno-pointer-arith
LFLAGS=-I./include/ -lpthread -I./
OBJS=Pogger.o Pid.o

main: $(OBJS) src/main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) src/main.cpp -o main

pid.o: src/Pid.cpp include/Pid.hpp
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) src/Pid.cpp -o Pid.o
	
logger.o: lib/src/Logger.cpp lib/include/Logger.hpp
	$(CXX) -c $(CXXFLAGS) $(LFLAGS) lib/src/Logger.cpp -o Logger.o
	
clean:
	rm -r -f *.o
	