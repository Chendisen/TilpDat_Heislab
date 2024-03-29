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

int sortOrder(Elevator elevator, Order order, int buttonArray[], Node* currentOrder){
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

    int n = (-1);

    if((int)motorDirection == (int)DIRN_UP){

        UP:

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

            n = numberOfOrders - upCabButtonsAbove - upCabButtonsBelowCurent - downButtons;
        }

        else if(((buttonType == BUTTON_HALL_DOWN) || (buttonType == BUTTON_CAB)) && (orderFloor <= currentFloor)){

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
                if((i%3 == 0) && (i > orderFloor * 3 + 2) && (i < currentFloor * 3 + 3) && (i > (int)orderFloor * 3 + 2)){
                    upButtonsAboveOrder += buttonArray[i];
                }
            }   

            n = numberOfOrders - upButtonsAboveOrder;
        }

        else if(buttonType == BUTTON_HALL_DOWN && orderFloor > currentFloor){
            int downButtonBelowOrder = 0;
            int upCabButtonBelowCurrent = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 1) && (i < orderFloor * 3)){
                    downButtonBelowOrder += buttonArray[i];
                }
                if((i%3 == 0 || i%3 == 2) && (i < currentFloor * 3 + 3)){
                    upCabButtonBelowCurrent += buttonArray[i];
                }
            }   

            n = numberOfOrders - downButtonBelowOrder - upCabButtonBelowCurrent;
        }

        return n;
    }    

    else if((int)motorDirection == (int)DIRN_DOWN){

        printf("inside second if\n");

        if((buttonType == BUTTON_HALL_DOWN || buttonType == BUTTON_CAB) && (orderFloor < currentFloor)){

            int downCabButtonsBelowOrder = 0;
            int upButtons = 0;
            int downCabButtonsAboveCurrent = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 1 || i%3 == 2) && (i < orderFloor * 3)){
                    downCabButtonsBelowOrder += buttonArray[i];
                }
                if(i%3 == 0){
                    upButtons += buttonArray[i];
                }
                if((i%3 == 1 || i%3 == 2) && ( i > currentFloor*3 - 1)){
                    downCabButtonsAboveCurrent += buttonArray[i];
                } 
            }   

            n = numberOfOrders - downCabButtonsAboveCurrent - downCabButtonsBelowOrder - upButtons;
        }

        else if(((buttonType == BUTTON_HALL_UP) || (buttonType == BUTTON_CAB)) && (orderFloor >= currentFloor)){

            int downButtonsAboveCurrent = 0;
            int upCabButtonsAboveOrder = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 1) && (i > currentFloor * 3 - 1)){
                    downButtonsAboveCurrent += buttonArray[i];
                }
                if((i%3 == 0 || i%3 == 2) && (i > orderFloor * 3 + 2)){
                    upCabButtonsAboveOrder += buttonArray[i];
                }
            }   

            n = numberOfOrders - downButtonsAboveCurrent - upCabButtonsAboveOrder;
        }

        else if(buttonType == BUTTON_HALL_DOWN && orderFloor >= currentFloor){

            int downButtonsBelowOrder = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 0) && (i > orderFloor * 3 + 2) && (i > currentFloor * 3 - 1) && (i < orderFloor * 3)){
                    downButtonsBelowOrder += buttonArray[i];
                }
            }   

            n = numberOfOrders - downButtonsBelowOrder;
        }

        else if(buttonType == BUTTON_HALL_UP && orderFloor < currentFloor){
            int upButtonAboveOrder = 0;
            int downCabButtonAboveCurrent = 0;

            for(int i = 0; i < 12; i++){
                if((i%3 == 0) && (i > orderFloor * 3 + 2)){
                    upButtonAboveOrder += buttonArray[i];
                }
                if((i%3 == 1 || i%3 == 2) && (i > currentFloor * 3 - 1)){
                    downCabButtonAboveCurrent += buttonArray[i];
                }
            }   

            n = numberOfOrders - upButtonAboveOrder - downCabButtonAboveCurrent;
        }

        return n;
    }  


    //########### DIRN STOP ############  

    else if(motorDirection == DIRN_STOP){
        printf("Inside third if\n");

        Node* temp = currentOrder->next;
        int ordersAtFloor = 1;

        while(temp != NULL){
            Floor tmpFloor = temp->thisOrder.floor;

            //DIRN UP

            if(tmpFloor > currentFloor){
                
                if((buttonType == BUTTON_HALL_UP || buttonType == BUTTON_CAB) && (orderFloor > currentFloor)){

                    int upCabButtonsAboveOrder = 0;
                    int downButtons = 0;
                    int upCabButtonsBelowCurrent = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 0 || i%3 == 2) && (i > orderFloor * 3 + 2)){
                            upCabButtonsAboveOrder += buttonArray[i];
                        }
                        if(i%3 == 1){
                            downButtons += buttonArray[i];
                        }
                        if((i%3 == 0 || i%3 == 2) && ( i < currentFloor * 3 + 3)){
                            upCabButtonsBelowCurrent += buttonArray[i];
                        } 
                    }   

                    n = numberOfOrders - upCabButtonsAboveOrder - upCabButtonsBelowCurrent - downButtons + ordersAtFloor;
                }

                else if(((buttonType == BUTTON_HALL_DOWN) || (buttonType == BUTTON_CAB)) && (orderFloor <= currentFloor)){

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

                    n = numberOfOrders - upButtonsBelowCurrent - downCabButtonsBelowOrder + ordersAtFloor;
                }

                else if(buttonType == BUTTON_HALL_UP && orderFloor <= currentFloor){

                    int upButtonsAboveOrder = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 0) && (i > orderFloor * 3 + 2) && (i < currentFloor * 3 + 3) && (i > (int)orderFloor * 3 + 2)){
                            upButtonsAboveOrder += buttonArray[i];
                        }
                    }   

                    n = numberOfOrders - upButtonsAboveOrder + ordersAtFloor;
                }

                else if(buttonType == BUTTON_HALL_DOWN && orderFloor > currentFloor){
                    int downButtonBelowOrder = 0;
                    int upCabButtonBelowCurrent = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 1) && (i < orderFloor * 3)){
                            downButtonBelowOrder += buttonArray[i];
                        }
                        if((i%3 == 0 || i%3 == 2) && (i < currentFloor * 3 + 3)){
                            upCabButtonBelowCurrent += buttonArray[i];
                        }
                    }   

                    n = numberOfOrders - downButtonBelowOrder - upCabButtonBelowCurrent + ordersAtFloor;
                }

                return n;
            }
            
            //DIRN DOWN

            else if(tmpFloor < currentFloor){
                if((buttonType == BUTTON_HALL_DOWN || buttonType == BUTTON_CAB) && (orderFloor < currentFloor)){

                    int downCabButtonsBelowOrder = 0;
                    int upButtons = 0;
                    int downCabButtonsAboveCurrent = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 1 || i%3 == 2) && (i < orderFloor * 3)){
                            downCabButtonsBelowOrder += buttonArray[i];
                        }
                        if(i%3 == 0){
                            upButtons += buttonArray[i];
                        }
                        if((i%3 == 1 || i%3 == 2) && ( i > currentFloor*3 - 1)){
                            downCabButtonsAboveCurrent += buttonArray[i];
                        } 
                    }   

                    n = numberOfOrders - downCabButtonsAboveCurrent - downCabButtonsBelowOrder - upButtons + ordersAtFloor;
                }

                else if(((buttonType == BUTTON_HALL_UP) || (buttonType == BUTTON_CAB)) && (orderFloor >= currentFloor)){

                    int downButtonsAboveCurrent = 0;
                    int upCabButtonsAboveOrder = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 1) && (i > currentFloor * 3 - 1)){
                            downButtonsAboveCurrent += buttonArray[i];
                        }
                        if((i%3 == 0 || i%3 == 2) && (i > orderFloor * 3 + 2)){
                            upCabButtonsAboveOrder += buttonArray[i];
                        }
                    }   

                    n = numberOfOrders - downButtonsAboveCurrent - upCabButtonsAboveOrder + ordersAtFloor;
                }

                else if(buttonType == BUTTON_HALL_DOWN && orderFloor >= currentFloor){

                    int downButtonsBelowOrder = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 0) && (i > orderFloor * 3 + 2) && (i > currentFloor * 3 - 1) && (i < orderFloor * 3)){
                            downButtonsBelowOrder += buttonArray[i];
                        }
                    }   

                    n = numberOfOrders - downButtonsBelowOrder + ordersAtFloor;
                }

                else if(buttonType == BUTTON_HALL_UP && orderFloor < currentFloor){
                    int upButtonAboveOrder = 0;
                    int downCabButtonAboveCurrent = 0;

                    for(int i = 0; i < 12; i++){
                        if((i%3 == 0) && (i > orderFloor * 3 + 2)){
                            upButtonAboveOrder += buttonArray[i];
                        }
                        if((i%3 == 1 || i%3 == 2) && (i > currentFloor * 3 - 1)){
                            downCabButtonAboveCurrent += buttonArray[i];
                        }
                    }   

                    n = numberOfOrders - upButtonAboveOrder - downCabButtonAboveCurrent + ordersAtFloor;
                }

                return n;
            }

            //CONTINUE

            else{
                temp = temp->next;
                ordersAtFloor++;
            }
        }


        return (-1);
    }

    printf("%d\n", n);

    return n;
}