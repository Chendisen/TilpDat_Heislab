#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"


typedef struct {
    int floorFrom;
    int floorTo;
    MotorDirection moveDirection;

}Order;


Order makeOrder(int floorF, int floorT, MotorDirection moveD);
