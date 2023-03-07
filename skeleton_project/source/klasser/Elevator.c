#include "Elevator.h"

Elevator makeElevator(Floor current, Floor desired, MotorDirection dir){
    Elevator newElevator;
    newElevator.currentFloor = current;
    newElevator.desiredFloor = desired;
    newElevator.direction = dir;
}

void setCurrentFloor(Elevator* elevatorPtr, Floor newCurrentFloor){
    elevatorPtr->currentFloor = newCurrentFloor;
};
void setDesiredFloor(Elevator* elevatorPtr, Floor newDesiredFloor){
    elevatorPtr->desiredFloor = newDesiredFloor;
};

void startEmergency(Elevator* elevatorPtr){
    elevatorPtr->desiredFloor = NONE;
    elevatorPtr->direction = DIRN_STOP;

};
