#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <queue>
#include <semaphore.h>

using namespace std;

int NUMBEROFSLEEPS = 0;
int NUMBEROFWORKS = 0;

void * produce(void *arg);
