#include "DoorHandler.h"


DoorHandler makeDoorHandler(){

    DoorHandler newDoorHandler;
    newDoorHandler.currentDoorState = CLOSED;
    newDoorHandler.obstruction = FALSE;

    return newDoorHandler;
}

void openDoor(DoorHandler *doorHandlerPtr){
    doorHandlerPtr->currentDoorState = OPEN;
    elevio_doorOpenLamp(1); 
}

void closeDoor(DoorHandler *doorHandlerPtr){
    doorHandlerPtr->currentDoorState = CLOSED;
    elevio_doorOpenLamp(0);
}

void setObstruction(DoorHandler *doorHandlerPtr, Bool obstruction){
    doorHandlerPtr->obstruction = obstruction;
}
 