# CXX = g++
# CXXFLAGS = -std=c++0x -Wall -Wextra -Werror -c

# OBJECTS = main.o queue.o TransandSleep.o consumer.o producer.o 

# prodcon: $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# $(OBJECTS):  TransandSleep.hpp queue.hpp consumer.hpp producer.hpp 

prodcon: main.o consumer.o producer.o queue.o TransandSleep.o
	g++ -pthread -Wall main.o consumer.o producer.o queue.o TransandSleep.o -o prodcon

main.o: main.cpp
	g++ -c main.cpp

consumer.o: consumer.cpp consumer.hpp
	g++ -c consumer.cpp 

producer.o: producer.cpp producer.hpp
	g++ -c producer.cpp

queue.o: queue.cpp queue.hpp
	g++ -c queue.cpp

TransandSleep.o: TransandSleep.cpp TransandSleep.hpp
	g++ -c TransandSleep.cpp

clean:
	rm *.o prodcon