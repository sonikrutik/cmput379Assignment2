// SOURCE: https://www.youtube.com/watch?v=l6zkaJFjUbM&t=634s
// Used this video quite a bit so I am going to leave it as a source here



#include "TransandSleep.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include "queue.hpp"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sstream>
#include <fstream>


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
    int perConsumerCompletes[NUMBER_OF_CONSUMERS];
    PER_CONSUMER_COMPLETES = &perConsumerCompletes[0];

    string prodcon = "prodcon";
    string log = ".log";
    string prodconFileName;

    if (argc >= 3){
        prodconFileName = prodcon + "." + argv[2] + log;
    }
    else{
        prodconFileName = prodcon + "." + "0" + log;
    }


    //cout << prodconFileName << "\n"; 
    
    

    // int id = 0;
    // int *idPointer = &id;
    // cout << *idPointer << "\n";
    // id++;
    // cout << *idPointer << "\n";

    //cout << "before thread creation";
    
    
    //cout << "after thread creation\n";   
    // freopen takes constant pointer, have to convert string to c_string
    

    // this initializes a semaphore of the number of used slots in the queue
    // Initially this would be 0 so initialize it at 0
    sem_init(&semUsed, 0, 0);
    // this initializes a semaphore wiht the number of UNused slots in the queue
    // of which the initial number is the BUFFER_SIZE
    sem_init(&semUnused, 0, BUFFER_SIZE);
    //mutex for accessing the buffer
    pthread_mutex_init(&bufferMutex, NULL);
    freopen(prodconFileName.c_str(), "w", stdout);
    pthread_t consumerThreads[NUMBER_OF_CONSUMERS];
    pthread_t producerThread;

    
    //cout << "after file open\n";
    //pthread_create can only use pointer arguments so create id pointer


    //cout << "before cons\n";
    //tried to create a pointer to 0 to pass as id  didnt work because i forgot 
    //that would cause a seg fault!!!!!!!!AHHHH
    if (pthread_create(&producerThread, NULL, &produce, NULL) != 0){
        fprintf(stderr, "Error creating producer thread");
    }
    //cout << "past cons\n";
    //https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
    //got idea to make thread list from this video and thsi website that had a few implementations and saw it in the textbook a couple times
    //https://www.youtube.com/watch?v=l6zkaJFjUbM&t=634s
    //cout << "before producing cons\n";
    for (int i = 1; i <= NUMBER_OF_CONSUMERS; i++){
        //from the lab
        int* idPointerC = (int*) malloc(sizeof(int));
        *idPointerC = i;
        if (pthread_create(&consumerThreads[i-1], NULL, &consumer, idPointerC) != 0){
            fprintf(stderr, "Error creating producer thread");
        }
    }
    //cout << "after producing cons\n";
    //Waits for the consumer thread to terminate execution 
    //error is non 0 value. If there is a 0 returned, print to stderr
    fprintf(stderr, "%u\n", (int)producerThread);
    if (pthread_join(producerThread, NULL) != 0){
        fprintf(stderr, "Failed to join Producer Thread\n");
    }
    // cout << "done prod join\n";
    //Waits for the threads to terminate execution
    //cant do join and create in the same loop because it will create the thread and wait for to join. 
    //this would not implement multithreaded programming
    //error is non 0 value. If there is a 0 returned, print the thread from the list
    //that casued an error
    //cout << "after join prod\n";
    for (int i = 0; i < NUMBER_OF_CONSUMERS; i++){
        fprintf(stderr, "%d: %u: ", i, (int)consumerThreads[i]);
        if (pthread_join(consumerThreads[i], NULL) != 0){
            fprintf(stderr, "Failed \n");
        }
    }
    //cout << "after join prod\n";
    // Destroy semaphores and mutex
    sem_destroy(&semUnused);
    sem_destroy(&semUsed);
    pthread_mutex_destroy(&bufferMutex);

    printf("Summary: \n");
    printf("    %-14s%d\n", "Work", NUMBEROFWORKS);
    printf("    %-14s%d\n", "Ask", NUMBEROFASKS);
    printf("    %-14s%d\n", "Receive", NUMBEROFRECEIVES);
    printf("    %-14s%d\n", "Complete", NUMBEROFCOMPLETES);
    printf("    %-14s%d\n", "Sleep", NUMBEROFSLEEPS);
    for (int i = 0; i < NUMBER_OF_CONSUMERS; i++){
        printf("    %s %2d%7d\n", "Thread", i+1, PER_CONSUMER_COMPLETES[i]);
    }

}