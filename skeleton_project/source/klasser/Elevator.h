#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"
#include "DoorHandler.h"

typedef enum {
    NONE = -1, 
    FIRST = 1,
    SECOND = 2, 
    THIRD = 3, 
    FOURTH = 4
} Floor;

typedef struct {
    Floor currentFloor;
    Floor desiredFloor;
    MotorDirection direction;
    Bool emergencyButton;
} Elevator;

Elevator makeElevator(Floor current, Floor desired, MotorDirection dir, Bool emergency);

void setCurrentFloor(Elevator* elevatorPtr, Floor floor);
void setDesiredFloor(Elevator* elevatorPtr, Floor floor);
void finishedDesiedFloor(Elevator* elevatorPtr);
void startEmergency(Elevator* elevatorPtr);
void stopeEmergency(Elevator* elevatorPtr);