#include "Elevator.h"

Elevator makeElevator(){
    Elevator newElevator;
    newElevator.currentFloor = NONE;
    newElevator.desiredFloor = NONE;
    newElevator.direction = DIRN_STOP;

    return newElevator;
}

void initiateElevator(Elevator* elevator){
    if(elevio_floorSensor() != -1){
        elevator->currentFloor = (Floor)elevio_floorSensor();
        return;
    }

    elevio_motorDirection(DIRN_DOWN);

    while(1){
        if(elevio_floorSensor() != -1){
            elevio_motorDirection(DIRN_STOP);
            elevator->currentFloor = (Floor)elevio_floorSensor();
            return;
        }
    }
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

void setMotorDirection(Elevator* elevatorPtr){
    if(elevatorPtr->desiredFloor == NONE || elevatorPtr->desiredFloor == elevatorPtr->currentFloor){
        elevatorPtr->direction = DIRN_STOP;
    }
    else if(elevatorPtr->currentFloor > elevatorPtr->desiredFloor){
        elevatorPtr->direction = DIRN_DOWN;
    }
    else if(elevatorPtr->currentFloor < elevatorPtr->desiredFloor){
        elevatorPtr->direction = DIRN_UP;
    }
    
    elevio_motorDirection(elevatorPtr->direction);
}
