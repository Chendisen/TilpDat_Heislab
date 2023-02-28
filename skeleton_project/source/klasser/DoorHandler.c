#include "DoorHandler.h"


DoorHandler makeDoorHandler(){

    DoorHandler newDoorHandler;
    newDoorHandler.currentDoorState = CLOSED;
    newDoorHandler.obstruction = FALSE;

    return newDoorHandler;
}

void openDoor(DoorHandler *DoorHandlerPtr){
    DoorHandlerPtr->currentDoorState = OPEN;
}

void closeDoor(DoorHandler *DoorHandlerPtr){
    DoorHandlerPtr->currentDoorState = CLOSED;
}

void setObstruction(DoorHandler *DoorHandlerPtr, Bool obstruction){
    DoorHandlerPtr->obstruction = obstruction;
}
