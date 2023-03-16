#include <signal.h>
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

    /*int ** matrix;

    for(int i = 0; i < 4; i++){
        matrix[i] = malloc(sizeof(int*) * 3);
        for(int j = 0; j < 3; j++){
            *matrix[i] = malloc(sizeof(int) *3 );
        }
    }*/

    Elevator elevator = makeElevator();
    DoorHandler doorHandler = makeDoorHandler();
    Timer timer = makeTimer(DOOR_TIME);
    FloorLight floorLight = makeFloorLight();
    Node* currentOrder = NULL;
    int buttonArray[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //Bool timerStarted = FALSE;
    Bool emergencyTriggered = FALSE;
    int emergencyIteration = 0;
    int sensorValue = 0;

    initiateElevator(&elevator); //Brings the elevator to a floor, and sets elevators current floor
    floorLightsOn(elevator.currentFloor, &floorLight); //Turns on the outside floorlight for that floor

    printf("=== Elevator has been initiated ===\n");

    while(1){
        emergencyIteration = 0;
        while(elevio_stopButton() == 1){ //Checks if emergency button is held down
            if(emergencyIteration == 0){ //Checks if we're in the first iteration, to make sure that the following functions dont run unnecessarily
                emergencyStop(&elevator); // Elevator stops

                if(currentOrder != NULL){ // Iterates through the list and turns off lights and removes every order
                    lightsOff(&currentOrder->thisOrder);
                    clearButtonPressed((int)currentOrder->thisOrder.floor, (int)currentOrder->thisOrder.buttonType, buttonArray); // Sets the button to 0 in button array
                } 
                Bool check = removeFirstNode(&currentOrder);
                while(check == TRUE){
                    if(currentOrder != NULL){
                        lightsOff(&currentOrder->thisOrder);
                        clearButtonPressed((int)currentOrder->thisOrder.floor, (int)currentOrder->thisOrder.buttonType, buttonArray); // Sets the button to 0 in button array
                    }
                    check = removeFirstNode(&currentOrder);
                }

                setDesiredFloor(&elevator, NONE); // Clears desired floor
                sensorValue = elevio_floorSensor();
                setCurrentFloor(&elevator, (Floor)sensorValue); // Sets current floor
                if(sensorValue != -1){ // Opens door if we're not between floors
                    openDoor(&doorHandler); 
                }
                emergencyTriggered = TRUE;
            }

            startTimer(&timer);
            emergencyIteration++;
        }

        for(int floor = (int)FIRST; floor <= (int)FOURTH; floor++){ //Iterating through all the buttons
            for(int buttonType = BUTTON_HALL_UP; buttonType <= BUTTON_CAB; buttonType++){
                if(elevio_callButton(floor, buttonType) && checkButtonPressed(floor, buttonType, buttonArray) == FALSE){ //Checks if a button is pushed
                    Order newOrder = makeOrder(buttonType, floor); //Makes a new order with correct floor and button type
                    lightsOn(&newOrder);  //Turns on the button lights for the order
                    int n = sortOrder(elevator, newOrder, buttonArray, currentOrder); // Finds which spot the order should be placed 
                    insertAtNth(&currentOrder, newOrder, n); // Adds the new orders to the list
                    setButtonPressed(floor, buttonType, buttonArray);
                    printf("Order is received\n");
                }
            }
        }

        if(emergencyTriggered == TRUE && currentOrder != NULL){ // If we just had an emergency and we now have a new order 
            initiateElevator(&elevator); // Gets elevator to known state, nothing happens if we're already in known state
            floorLightsOn(elevator.currentFloor, &floorLight); 
            emergencyTriggered = FALSE;
        }

        if(currentOrder != NULL && doorHandler.currentDoorState == CLOSED){
            setDesiredFloor(&elevator, currentOrder->thisOrder.floor); //Changes the elevators desired floor to the orders target floor
            setMotorDirection(&elevator); //Sets elevator motor direction based on elevators current- and desired floor
        }

        sensorValue = elevio_floorSensor();
        if( sensorValue != -1){ //Checks if we are in a specific floor
            setCurrentFloor(&elevator, (Floor)(sensorValue)); //Sets the elevators current floor to that floor
            floorLightsOn((Floor)sensorValue, &floorLight); //Turns on the outside floorlights for that floor
        }

        if(currentOrder != NULL && elevator.currentFloor == elevator.desiredFloor && doorHandler.currentDoorState == CLOSED){ // In desired floor and door is closed
            openDoor(&doorHandler);
            Floor check = currentOrder->thisOrder.floor;
            Node* temp = currentOrder;
            while(temp != NULL && temp->thisOrder.floor == check){
                lightsOff(&temp->thisOrder);
                temp = temp->next;
            }
            startTimer(&timer);
            setMotorDirection(&elevator); // Stops motor
            //timerStarted = TRUE;
        }

        if (elevio_obstruction() == 1){ // Checks if obstruction is set
            doorHandler.obstruction = TRUE;

            if(doorHandler.currentDoorState == OPEN){ // If door is open at the same time, the timer resets
                resetTimer(&timer);
            }
        }
        if (elevio_obstruction() == 0){
            doorHandler.obstruction = FALSE;
        }

        //printf("%d \n", (int)checkTimer(&timer));
        //printf("%d \n", elevio_obstruction());

        if(elevio_obstruction() == 0 && emergencyTriggered == TRUE && checkTimer(&timer) == TRUE){
            closeDoor(&doorHandler);
            emergencyTriggered = FALSE;
        }

        if(elevio_obstruction() == 0 && emergencyTriggered == FALSE && checkTimer(&timer) == TRUE){ // Cheks if timer has run out and resets it if it has
            printf("0\n");
            closeDoor(&doorHandler);
            printf("2\n");
            Floor check = currentOrder->thisOrder.floor;
            while(currentOrder != NULL && currentOrder->thisOrder.floor == check){
                clearButtonPressed((int)currentOrder->thisOrder.floor, (int)currentOrder->thisOrder.buttonType, buttonArray);
                removeFirstNode(&currentOrder);
            }
            printf("3\n");
            //timerStarted = FALSE;
        }

    }


    //HEi CHRS


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
