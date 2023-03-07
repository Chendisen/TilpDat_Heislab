#include "Elevator.h"

Elevator makeElevator(Floor current, Floor desired, MotorDirection dir, Bool emergency){
    Elevator newElevator;
    newElevator.currentFloor = current;
    newElevator.desiredFloor = desired;
    newElevator.direction = dir;
    newElevator.emergencyButton = emergency;
}

void setCurrentFloor(Elevator* elevatorPtr, Floor newCurrentFloor){
    elevatorPtr->currentFloor = newCurrentFloor;
};
void setDesiredFloor(Elevator* elevatorPtr, Floor newDesiredFloor){
    elevatorPtr->desiredFloor = newDesiredFloor;
};
void finishedDesiedFloor(Elevator* elevatorPtr){
    
};
void startEmergency(Elevator* elevatorPtr);
void stopeEmergency(Elevator* elevatorPtr);