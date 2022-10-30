#ifndef PRODUCER_HPP
#define PRODUCER_HPP


#include "queue.hpp"
#include "TransandSleep.hpp"

#include <cstdio>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

extern int NUMBEROFSLEEPS;
extern int NUMBEROFWORKS;

void * produce(void *idPointer);
#endif 