#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "queue.hpp"
#include "TransandSleep.hpp"

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

//need to track total tasks completed and per thread task completed
extern int NUMBEROFASKS;
extern int NUMBEROFRECEIVES;
extern int NUMBEROFCOMPLETES;


void * consumer(void *idPointer);
#endif