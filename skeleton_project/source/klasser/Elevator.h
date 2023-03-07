#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"
#include "DoorHandler.h"

typedef struct {
    Floor currentFloor;
    Floor desiredFloor;
    MotorDirection direction;
} Elevator;

Elevator makeElevator(Floor current, Floor desired, MotorDirection dir);

void setCurrentFloor(Elevator* elevatorPtr, Floor floor);
void setDesiredFloor(Elevator* elevatorPtr, Floor floor);
void startEmergency(Elevator* elevatorPtr);
