#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../driver/elevio.h"


typedef enum{
    OPEN,
    CLOSED
} DoorState;

typedef struct{
    DoorState currentDoorState;
    Bool obstruction;

} DoorHandler;


DoorHandler makeDoorHandler();


void openDoor(DoorHandler *doorHandlerPtr);
void closeDoor(DoorHandler *doorHandlerPtr);
void setObstruction(DoorHandler *doorHandlerPtr, Bool obstruction); 