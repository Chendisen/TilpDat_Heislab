#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

typedef struct Order{
    int floorFrom;
    int floorTo;
    MotorDirection moveDirection;

    Order* nextOrder = nullptr;
    Order* prevOrder = nullptr;

    void (*setNextOrder)(Order* nextOrder, Order& thisOrder);
    void (*setPrevOrder)(Order* PrevOrder, Order& thisOrder);
}Order;

void setNextOrder(Order* next, Order& this);


