CXX = g++
CXXFLAGS = -Wall -g

OBJECTS = main.o queue.o TransandSleep.o consumer.o producer.o 

prodcon: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS):  TransandSleep.hpp queue.hpp consumer.hpp producer.hpp 
