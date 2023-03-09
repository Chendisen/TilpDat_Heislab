#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../driver/elevio.h"


typedef struct{
    int seconds;
    clock_t startTime;
} Timer;

Timer makeTimer(int seconds);

void startTimer(Timer *timerPtr);
void resetTimer(Timer *timerPtr);
Bool checkTimer(Timer *timerPtr);