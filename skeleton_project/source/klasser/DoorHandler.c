#include "DoorHandler.h"


DoorHandler makeDoorHandler(){

    DoorHandler newDoorHandler;
    newDoorHandler.currentDoorState = CLOSED;
    newDoorHandler.obstruction = FALSE;

    return newDoorHandler;
}

void openDoor(DoorHandler *doorHandlerPtr){
    doorHandlerPtr->currentDoorState = OPEN;
}

void closeDoor(DoorHandler *doorHandlerPtr){
    doorHandlerPtr->currentDoorState = CLOSED;
}

void setObstruction(DoorHandler *doorHandlerPtr, Bool obstruction){
    doorHandlerPtr->obstruction = obstruction;
}
