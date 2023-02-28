#include "Order.h"

void setNextOrder(Order* next, Order* this){
    this->nextOrder = next;
};

void setPrevOrder(Order* prev, Order* this){
    this->prevOrder = prev;
};

Order makeOrder(int floorF, int floorT, MotorDirection moveD, Order* next, Order* prev){
    Order newOrder;
    
    newOrder.floorFrom = floorF;
    newOrder.floorTo = floorT;
    newOrder.moveDirection = moveD;
    newOrder.nextOrder = next;
    newOrder.prevOrder = prev;

    return newOrder;
};