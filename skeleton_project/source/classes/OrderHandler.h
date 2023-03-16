#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"
#include "Order.h"
#include "Elevator.h"

Bool checkButtonPressed(int floor, int buttonType, int buttonArray[]);
void setButtonPressed(int floor, int buttonType, int buttonArray[]);
void clearButtonPressed(int floor, int buttonType, int buttonArray[]);

typedef struct Node{
    Order thisOrder;
    struct Node* next;
} Node;

void insertAtNth(Node** head, Order newOrder, int n);
Bool removeFirstNode(Node** head);
int sortOrder(Elevator elevator, Order order, int buttonArray[], Node* currentOrder);
