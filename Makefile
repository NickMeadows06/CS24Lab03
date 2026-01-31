CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

all: testbst

testbst: intbst.o testbst.o
	$(CXX) $(CXXFLAGS) -o testbst intbst.o testbst.o

intbst.o: intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c intbst.cpp

testbst.o: testbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c testbst.cpp

clean:
	rm -f testbst *.o