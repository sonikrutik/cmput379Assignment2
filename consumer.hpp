#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <queue>
using namespace std;

//need to track total tasks completed and per thread task completed
int NUMBEROFASKS = 0;
int NUMBEROFRECEIVES = 0;
int NUMBEROFCOMPLETES = 0;

struct consumerThread{
    int consumerID;
    int tasksCompleted;
};
void * consumer(void *arg);