#include "OrderHandler.h"


void insertAtNth(Node** head, Order newOrder, int n){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->thisOrder = newOrder;
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
        return;
    }

    if(n == 0){
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* temp = *head;

    if(n == -1){
        while(1){
            if (temp->next == NULL) {
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }   
            temp = temp->next;
        }
    }
    
    for(int i = 0; i < n-1; i++){
        if (temp->next == NULL) {
            printf("Error: Invalid position\n");
            return;
        }   
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

Bool removeFirstNode(Node** head){
    if(*head == NULL){
        printf("The linked list is empty!\n");
        return FALSE;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);

    return TRUE;
}

Bool checkButtonPressed(int floor, int buttonType, int buttonArray[]){
    return (Bool)buttonArray[floor*3 + buttonType];
}

void setButtonPressed(int floor, int buttonType, int buttonArray[]){
    buttonArray[floor*3 + buttonType] = 1;
}

void clearButtonPressed(int floor, int buttonType, int buttonArray[]){
    buttonArray[floor*3 + buttonType] = 0;
}

int sortOrder(Elevator elevator, Order order, int buttonArray[]){
    Floor orderFloor = order.floor;
    Floor currentFloor = elevator.currentFloor;

    ButtonType buttonType = order.buttonType; 
    MotorDirection motorDirection = elevator.direction;

    int numberOfOrders = 0;

    for(int i = 0; i < 12; i++){
        numberOfOrders += buttonArray[i];
    }

    if(numberOfOrders == 0){
        return (-1);
    }

    printf("MotorDir: %d\n", (int)motorDirection);
    printf("ButtonType: %d\n", (int)buttonType);
    printf("CurrentFloor: %d\n", (int)currentFloor);
    printf("OrderFloor: %d\n", (int)orderFloor);
    printf("NumberOfOrders: %d\n", (int)numberOfOrders);


    int n = (-1);

    if((int)motorDirection == (int)DIRN_UP){

        printf("inside first if\n");

        if((buttonType == BUTTON_HALL_UP || buttonType == BUTTON_CAB) && (orderFloor > currentFloor)){

            int upCabButtonsAbove = 0;
            int downButtons = 0;
            int upCabButtonsBelowCurent = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 0 || i%3 == 2) && (i > orderFloor * 3 + 2)){
                    upCabButtonsAbove += buttonArray[i];
                }
                if(i%3 == 1){
                    downButtons += buttonArray[i];
                }
                if((i%3 == 0 || i%3 == 2) && ( i < currentFloor*3 + 3)){
                    upCabButtonsBelowCurent += buttonArray[i];
                } 
            }   

            printf("upCabAbove: %d\n", (int)upCabButtonsAbove);
            printf("DownButtons: %d\n", (int)downButtons);
            printf("upCabBelowCurrent: %d\n", (int)upCabButtonsBelowCurent);

            n = numberOfOrders - upCabButtonsAbove - upCabButtonsBelowCurent - downButtons;

            printf("N: %d\n", (int)n);

        }

        else if(((buttonType == BUTTON_HALL_DOWN) || (buttonType == BUTTON_CAB)) && (orderFloor < currentFloor)){

            int upButtonsBelowCurrent = 0;
            int downCabButtonsBelowOrder = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 0) && (i < currentFloor * 3 + 3)){
                    upButtonsBelowCurrent += buttonArray[i];
                }
                if((i%3 == 1 || i%3 == 2) && (i < orderFloor * 3)){
                    downCabButtonsBelowOrder += buttonArray[i];
                }
            }   

            n = numberOfOrders - upButtonsBelowCurrent - downCabButtonsBelowOrder;
        }

        else if(buttonType == BUTTON_HALL_UP && orderFloor <= currentFloor){

            int upButtonsAboveOrder = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 0) && (i > orderFloor * 3 + 2) && (i < currentFloor * 3 + 3)){
                    upButtonsAboveOrder += buttonArray[i];
                }
            }   

            n = numberOfOrders - upButtonsAboveOrder;
        }
    }    

    printf("%d\n", n);

    return n;
}