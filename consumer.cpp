#include "consumer.hpp"
#include "queue.hpp"




void * consumer(void *idPointer){
    //have to typecast to int* and then dereference to be able to assign to consumerID of consumerThread
    int consID = * (int*) idPointer;

    cout << idPointer;

    consumerThread aConsumerThread;
    aConsumerThread.consumerID = consID;
    aConsumerThread.tasksCompleted = 0;

    //eof char is set to 0, when producer put eof into queue it it will be reset to -1
    int eof = 0;

    while 
    
}