#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

class Order{
    int floorFrom;
    int floorTo;
    MotorDirection moveDirection;
public:
    Order(int from = 0, int to = 0, MotorDirection direction = DIRN_STOP) : floorFrom{from}, floorTo{to}, moveDirection{direction} {};
    int getFloorFrom();
    int getFloorTo();
    MotorDirection getMoveDirection();
};