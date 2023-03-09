#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "classes/DoorHandler.h"
#include "classes/Elevator.h"
#include "classes/FloorLight.h"
#include "classes/Order.h"
#include "classes/Timer.h"
#include "classes/OrderHandler.h"


int main(){
    elevio_init();
    

    printf("=== Welcome to the Elevator Program ===\n");
    printf("=== Initiating Elevator ===\n");

    Elevator elevator = makeElevator();
    DoorHandler doorHandler = makeDoorHandler();
    Timer timer = makeTimer(DOOR_TIME);
    FloorLight floorLight = makeFloorLight();
    Node* currentOrder = NULL;
    Bool timerStarted = FALSE;
    Bool emergencyTriggered = FALSE;

    initiateElevator(&elevator); //Brings the elevator to a floor, and sets elevators current floor
    floorLightsOn(elevator.currentFloor, &floorLight); //Turns on the outside floorlight for that floor

    printf("=== Elevator has been initiated ===\n");


    while(1){
        while(elevio_stopButton()){ //Checks if emergency button is held down
            int i = 0;
            if(!i){ //Checks if we're in the first iteration, to make sure that the following functions dont run unnecessarily
                clearList(&currentOrder); //Clears the list of orders
                setDesiredFloor(&elevator, NONE); //Clears desired floor
                setCurrentFloor(&elevator, (Floor)elevio_floorSensor()); //Sets current floor
                if(elevio_floorSensor() != -1){
                    openDoor(&doorHandler);
                }
                emergencyTriggered = TRUE;
            }
            i++;
        }

        for(int floor = (int)FIRST-1; floor <= (int)FOURTH-1; floor++){ //Iterating through all the buttons
            for(int buttonType = BUTTON_HALL_UP; buttonType <= BUTTON_CAB; buttonType++){
                if(elevio_callButton(floor, buttonType)){ //Checks if a button is pushed
                    Order newOrder = makeOrder(buttonType, floor); //Makes a new order with correct floor and button type
                    lightsOn(&newOrder);  //Turns on the button lights for the order
                    insertAtNth(&currentOrder, newOrder, -1); // Adds the new orders to the list
                }
            }
        }
        
        if(emergencyTriggered && currentOrder != NULL){ //If we just had an emergency and, and we now have a new order 
            if(elevio_floorSensor() != -1){  //If we are already in a floor, the door should open for 3 seconds
                startTimer(&timer); //Starts the countdown
                timerStarted = TRUE; //
            }
            initiateElevator(&elevator);
            floorLightsOn(elevator.currentFloor, &floorLight);
            emergencyTriggered = FALSE;
        }

        if(currentOrder != NULL && doorHandler.currentDoorState == CLOSED){
            setDesiredFloor(&elevator, currentOrder->thisOrder.floor); //Changes the elevators desired floor to the orders target floor
            setMotorDirection(&elevator); //Sets elevator motor direction based on elevators current- and desired floor
        }

        if(elevio_floorSensor() != -1){ //Checks if we ar in a specific floor
            setCurrentFloor(&elevator, (Floor)(elevio_floorSensor())); //Sets the elevators current floor to that floor
            floorLightsOn((Floor)elevio_floorSensor(), &floorLight); //Turns on the outside floorlights for that floor
        }

        if(currentOrder != NULL && elevator.currentFloor == elevator.desiredFloor && !timerStarted){
            openDoor(&doorHandler);
            startTimer(&timer);
            timerStarted = TRUE;
        }

        if(checkTimer(&timer)){
            if(!doorHandler.obstruction){
                closeDoor(&doorHandler);
            }
    
            lightsOff(&currentOrder->thisOrder);
            removeFirstNode(&currentOrder);
            timerStarted = FALSE;
        }

    }

    /*
    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }*/

    return 0;
}
