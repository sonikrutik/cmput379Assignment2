#include "consumer.hpp"

int NUMBEROFASKS = 0;
int NUMBEROFRECEIVES = 0;
int NUMBEROFCOMPLETES = 0;

struct aConsumerThread{
    int id;
    int threadWorks = 0;
};


void * consumer(void *idPointer){
    //have to typecast to int* and then dereference to be able to assign to consumerID of consumerThread
    int consID = * (int*) idPointer;

    cout << idPointer << "\n";
    cout << consID << "\n";

    aConsumerThread consThread;
    consThread.id = consID;


    //eof char is set to 0, when producer put eof into queue it it will be reset to -1
    int eof = 0;

    while (eof != EOF){
        //ask print does not need to be inside the semaphore since threads can ask and 
        //sample output shows we print whenever consumer thread asks for work
        int n;
        pthread_mutex_lock(&bufferMutex);
        printf("%.3f ID=%2d      %-14s\n", 0.000, consThread.id, "Ask");
        NUMBEROFASKS = NUMBEROFASKS + 1;
        pthread_mutex_unlock(&bufferMutex);

        

        //we sem_wait on semUsed in the consumer thread because the consumer thread will be trying to reduce
        //the number of used positions in the queue. when semUsed is at 0, consumer will wait here until 
        //producer has produced something into the queue and sem_posted onto semUsed
        sem_wait(&semUsed);
        pthread_mutex_lock(&bufferMutex);
        // inside crit section, grab whats at the front of the queue and pop it
        // pop queue doesnt return the value so have to grab from front first
        n = commands.front();
        commands.pop();
        if (n != EOF){
            //0.000 ID= 1 Q= 1 Receive
            printf("%.3f ID=%2d Q=%2d %-14s %d\n", 0.000, consThread.id, (int)commands.size(), "Work", n);
            NUMBEROFRECEIVES = NUMBEROFRECEIVES + 1;
        
        }
        //now since consumer has consumed a command from the queue, we post to unused
        //so that if the queue was at its maxSize, the producer can produce one more command without
        //worrying about the bounding 
        pthread_mutex_unlock(&bufferMutex);
        sem_post(&semUnused);

        if (n != EOF){
            Trans(n);
            NUMBEROFCOMPLETES = NUMBEROFCOMPLETES + 1;

            pthread_mutex_unlock(&bufferMutex);
            //go to index of the consumer thread, increase its threadworks by one and ptu it into th elist
            consThread.threadWorks = consThread.threadWorks + 1;
            PER_CONSUMER_COMPLETES[consThread.id - 1] = consThread.threadWorks;
            printf("%.3f ID=%2d      %-14s %d\n", 0.000, consThread.id, "Complete", n);
            pthread_mutex_lock(&bufferMutex);
        }
        

    }
    
    free(idPointer);
    return 0;
}