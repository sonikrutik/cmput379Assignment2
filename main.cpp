// SOURCE: https://www.youtube.com/watch?v=l6zkaJFjUbM&t=634s
// Used this video quite a bit so I am going to leave it as a source here

#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <queue>
#include <semaphore.h>

#include "TransandSleep.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include "queue.hpp"

using namespace std;



int main(int argc, char *argv[]){
    //check there are atleast 2 arguments given to prodcon
    if (argc < 2){
        cout << "Not enough arguments given to prodcon" << "\n";
        return 0;
    }

    //default initialize fileid to 0
    NUMBER_OF_CONSUMERS = atoi(argv[1]);
    BUFFER_SIZE = NUMBER_OF_CONSUMERS * 2;

    int fileID = 0;
    string prodcon = "prodcon";
    string log = ".log";
    string prodconFileName;

    if (argc >= 3){
        prodconFileName = prodcon + "." + argv[2] + log;
    }
    else{
        prodconFileName = prodcon + "." + "0" + log;
    }


    cout << prodconFileName << "\n"; 
    
    

    // int id = 0;
    // int *idPointer = &id;
    // cout << *idPointer << "\n";
    // id++;
    // cout << *idPointer << "\n";

    
    pthread_t producerThread;
    pthread_t consumerThreads[NUMBER_OF_CONSUMERS];

    // freopen takes constant pointer, have to convert string to c_string
    freopen(prodconFileName.c_str(), "w", stdout);

    //pthread_create can only use pointer arguments so create id pointer
    int id = 0;
    int *idPointer = &id;

    // this initializes a semaphore of the number of used slots in the queue
    // Initially this would be 0 so initialize it at 0
    sem_init(&semUsed, 0, 0);

    // this initializes a semaphore wiht the number of UNused slots in the queue
    // of which the initial number is the BUFFER_SIZE
    sem_init(&semUnused, 0, BUFFER_SIZE);
    //mutex for accessing the buffer
    pthread_mutex_init(&bufferMutex, NULL);

    if (pthread_create(&producerThread, NULL, produce, idPointer) != 0){
        fprintf(stderr, "Error creating producer thread");
    }

    //https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
    //got idea to make thread list from this video and thsi website that had a few implementations
    //https://www.youtube.com/watch?v=l6zkaJFjUbM&t=634s
    id++; 
    cout << id;
    for (id; id < NUMBER_OF_CONSUMERS + 1; id++){
        if (pthread_create(&consumerThreads[id - 1], NULL, &consumer, idPointer) != 0){
            fprintf(stderr, "Error creating producer thread");
        }
    }

    //Waits for the consumer thread to terminate execution 
    //error is non 0 value. If there is a 0 returned, print to stderr
    if (pthread_join(producerThread, NULL) != 0){
        fprintf(stderr, "Failed to join Producer Thread\n");
    }
    //Waits for the threads to terminate execution
    //error is non 0 value. If there is a 0 returned, print the thread from the list
    //that casued an error
    for (int i = 0; i < NUMBER_OF_CONSUMERS; i++){
        if (pthread_join(consumerThreads[i], NULL) != 0){
            fprintf(stderr, "Failed to join thread %d\n", i);
        }
    }
    
    // Destroy semaphores and mutex
    sem_destroy(&semUnused);
    sem_destroy(&semUsed);
    pthread_mutex_destroy(&bufferMutex);

}