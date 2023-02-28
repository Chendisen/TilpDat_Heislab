#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

struct Timer{
    int seconds;
    void (*startTimerPtr)(int seconds);
    void (*resetTimerPtr)();
};

struct Timer makeTimer(int seconds){};

void startTimer(int seconds);
void resetTimer();