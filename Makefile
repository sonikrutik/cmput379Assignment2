CXX = g++
CXXFLAGS = -Wall -g

OBJECTS = main.o TransandSleep.o

prodcon: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS):  TransandSleep.hpp
