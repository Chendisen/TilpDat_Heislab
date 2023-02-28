#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

typedef struct {
    int floorFrom;
    int floorTo;
    MotorDirection moveDirection;

    Order* nextOrder;
    Order* prevOrder;
}Order;

void setNextOrder(Order* next, Order* this);
void setPrevOrder(Order* prev, Order* this);

Order makeOrder(int floorF, int floorT, MotorDirection moveD, Order* next, Order* prev);
