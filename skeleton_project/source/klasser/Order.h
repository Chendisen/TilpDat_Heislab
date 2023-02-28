#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"

typedef enum{
    UP,
    DOWN
} Direction;

typedef struct {
    int floorFrom;
    int floorTo;
    Direction moveDirection;

}Order;


Order makeOrder(int floorF, int floorT, Direction moveD);
