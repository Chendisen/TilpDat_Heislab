#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"


typedef struct{
    int seconds;
} Timer;

Timer makeTimer(int seconds);

void startTimer(Timer *TimerPtr);
void resetTimer(Timer *TimerPtr);