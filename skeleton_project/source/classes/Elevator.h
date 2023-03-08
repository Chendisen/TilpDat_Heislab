#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"
#include "DoorHandler.h"

typedef struct {
    Floor currentFloor;
    Floor desiredFloor;
    MotorDirection direction;
} Elevator;

Elevator makeElevator();

void initiateElevator();
void setCurrentFloor(Elevator* elevatorPtr, Floor floor);
void setDesiredFloor(Elevator* elevatorPtr, Floor floor);
void startEmergency(Elevator* elevatorPtr);
void setMotorDirection(Elevator* elevatorPtr);
 