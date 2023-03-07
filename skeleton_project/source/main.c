#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "classes/DoorHandler.h"
#include "classes/Elevator.h"
#include "classes/FloorLight.h"
#include "classes/Order.h"
#include "classes/OrderHandler.h"
#include "classes/Timer.h"


int main(){
    elevio_init();
    

    printf("=== Welcome to the Elevator Program ===\n");
    printf("=== Initiating Elevator ===\n");

    Elevator elevator = makeElevator();
    DoorHandler doorHandler = makeDoorHandler();
    Timer timer = makeTimer(DOOR_TIME);
    FloorLight floorLight = makeFloorLight();
    Node* currentOrder = NULL;

    initiateElevator(&elevator); //Brings the elevator to a floor, and sets elevators current floor
    floorLightsOn(elevator.currentFloor, &floorLight); //Turns on the outside floorlight for that floor

    printf("=== Elevator has been initiated ===\n");


    while(1){
        for(int floor = (int)FIRST-1; floor <= (int)FOURTH-1; floor++){
            for(int buttonType = BUTTON_HALL_UP; buttonType <= BUTTON_CAB; buttonType++){
                printf("%d", elevio_callButton(floor, buttonType));
                if(elevio_callButton(floor, buttonType)){
                    Order newOrder = makeOrder(buttonType, floor); 
                    lightsOn(&newOrder);
                    insertAtNth(&currentOrder, newOrder, -1); // Adds all new orders to the list, and turns on lights
                }
            }
        }

        if (currentOrder != NULL){
            setDesiredFloor(&elevator, currentOrder->thisOrder.floor); //Changes the elevators desired floor to the orders target floor
            setMotorDirection(&elevator); //Sets elevator motor direction based on elevators current- and desired floor
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
