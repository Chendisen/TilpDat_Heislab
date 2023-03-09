#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"


typedef enum{
    OPEN = 1,
    CLOSED = 0
} DoorState;

typedef struct{
    DoorState currentDoorState;
    Bool obstruction;

} DoorHandler;


DoorHandler makeDoorHandler();


void openDoor(DoorHandler *doorHandlerPtr);
void closeDoor(DoorHandler *doorHandlerPtr);
void setObstruction(DoorHandler *doorHandlerPtr, Bool obstruction); 