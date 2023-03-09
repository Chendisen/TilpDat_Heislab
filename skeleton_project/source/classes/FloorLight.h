#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"
#include "Elevator.h"


typedef struct{
    Floor currentLight;
} FloorLight;

FloorLight makeFloorLight();

void floorLightsOn(Floor currentFloor, FloorLight *floorLightPtr); 

