CXX=c++
CXXFLAGS=-std=c++11

all:$(patsubst %.cpp, %.out, $(wildcard *.cpp))
#all:$( %.cpp, %.out, $(wildcard*.cpp))

%.out: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $< -o $@
