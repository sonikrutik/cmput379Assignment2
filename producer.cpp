
#include "producer.hpp"
#include "TransandSleep.hpp"
#include "queue.hpp"

struct producerThread{
    int id;
};

void * produce(void *idPointer){
    //producer id should be 0
    int prodID = * (int*) idPointer;
    producerThread prodThread;
    prodThread.id = prodID;

    char cmd[3*sizeof(char)];
    int n;

    while ((scanf("%s\n", &cmd)) != EOF){
        n = int(cmd[1]);

        if (cmd[0] == 'S'){
            //if there is a sleep command, you can execute it right away since the producer
            //has nothing to do with this. The command does not need to wait in the queue
            //add one to the counter of NUMBEROFSLEEPS to be able to print at the end of the execution of the program
            Sleep(n);
            printf("%.3f ID=%2d      %-14s %d", 0.000, prodThread.id, "Sleep", n);
            NUMBEROFSLEEPS = NUMBEROFSLEEPS + 1;
        }
        // case where cmd[0] == T
        else{
            //here now the producer has a item that it can add to the queue
            //use the semUnused semaphore and wait on it to decrement the current 
            //number of unused elements in the buffer
            //this basically means that the producer is going to try to add something to the queue
            //so semUnused is going to decrement
            //this makes it so we only produce max number of commands at a time
            //and the mutex makes it so neither producer and consumer can have
            //hands in the buffer at the same time
            sem_wait(&semUnused);
            pthread_mutex_lock(&bufferMutex);
            // and finally we can push the command n to queue
            commands.push(n);
            //            0.000 ID= 0 Q= 1 Work 4                         // Parent receives work with n=4
            printf("%.3f ID=%2d Q=%2d %-14s %d\n", 0.000, prodThread.id, "Work", n);
            NUMBEROFWORKS = NUMBEROFWORKS + 1;
            
            pthread_mutex_unlock(&bufferMutex);
            // Now we post to semUsed to show to the consumers that there is something in the 
            // that we can consume from and the consumer can sem_wait semUsed once its gets past its semaphore
            sem_post(&semUsed);
        }

        //0.100 ID= 0 End 
        printf("%0.3f ID=%2d      %-14s", 0.100, prodThread.id, "End");

        if(cmd[-1] == EOF){
            // we reached the end of file so no more commands remain to be checked
            // notify all the producers that we are done and that they can exit their while loops
            // we need to do this in a way that the queue isnt pumped so we need to do it in a loop so that 
            // once there is a unused slot in the queue, we push EOF that eventually kills a thread that
            // grabs that EOF element from the queue
            // Since we try to kill all the threads, we do this for the number of threads in we created so...
            int i = 0;
            while (i < BUFFER_SIZE){
                sem_wait(&semUnused);
                pthread_mutex_lock(&bufferMutex);
                commands.push(EOF);
                pthread_mutex_unlock(&bufferMutex);
                sem_post(&semUsed);
                i++;
            }
            


        }

}