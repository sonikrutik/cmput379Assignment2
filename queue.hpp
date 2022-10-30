#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <semaphore.h>
#include <queue>
#include <pthread.h>

using namespace std;

extern int NUMBER_OF_CONSUMERS;
extern int BUFFER_SIZE;
//creating global pointer to access a list which contains completes for each consumer
extern int *PER_CONSUMER_COMPLETES;
//putting semaphores here so dont have to make mainhpp file
//one semaphore for when producer must stop producing
//one semaphore for when consumer must stop consuming
extern sem_t semUsed;
extern sem_t semUnused;
//one mutex for letting prod and cons access the buffer
extern pthread_mutex_t bufferMutex;

//using a queue to make pushing and popping easier. 
//queue only needs the int since if the producer recieves a S command
//it sleeps in it's own thread and consumer nor the queue need to know 
//about this command
//buffer only will contain T commands that the consumer threads must consume
extern queue<int> commands;

#endif