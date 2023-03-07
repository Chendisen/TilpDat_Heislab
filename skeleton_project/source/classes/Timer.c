#include "Timer.h"

Timer makeTimer(int seconds){
    Timer newTimer;
    newTimer.seconds = seconds;
    newTimer.startTime = 0.0;

    return newTimer;
}

void startTimer(Timer *timerPtr){
    timerPtr->startTime = clock();
}

void resetTimer(Timer *timerPtr){
    timerPtr->startTime = clock();
}

Bool checkTimer(Timer *timerPtr){
    if (timerPtr->startTime == 0.0){
        return FALSE;
    }

    clock_t currentTime = clock();
    if (difftime(currentTime, timerPtr->startTime) > timerPtr->seconds){
        timerPtr->startTime = 0.0;

        return TRUE;
    }

    return FALSE;
}