#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"
#include "Order.h"


typedef struct Node{
    Order thisOrder;
    struct Node* next;
} Node;

void insertAtNth(Node** head, Order newOrder, int n);
Bool removeFirstNode(Node** head);
void clearList(Node** head); 
