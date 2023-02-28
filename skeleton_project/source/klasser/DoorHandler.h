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

typedef enum{
    TRUE,
    FALSE
} Bool;

typedef struct{
    DoorState currentDoorState;
    Bool obstruction;

} DoorHandler;


DoorHandler makeDoorHandler();


void openDoor(DoorHandler *DoorHandlerPtr);
void closeDoor(DoorHandler *DoorHandlerPtr);
void setObstruction(DoorHandler *DoorHandlerPtr, Bool obstruction);