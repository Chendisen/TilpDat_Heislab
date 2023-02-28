#include "Timer.h"

Timer makeTimer(int seconds){
    Timer newTimer;
    newTimer.seconds = seconds;

    return newTimer;
}