#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"
#include "Order.h"

typedef enum {
    INSIDE, 
    OUTSIDE
} LightType;

typedef enum {
    NONE, 
    FIRST,
    SECOND, 
    THIRD, 
    FOURTH
} Floor;

typedef struct {
    LightType lightType;
    Floor floor;
    MotorDirection direction;

} ReservationLight;

void lightsOn(Order* order, ReservationLight* ReservationLightPtr);