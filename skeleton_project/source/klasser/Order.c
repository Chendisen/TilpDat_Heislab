#include "Order.h"


Order makeOrder(int floorF, int floorT, MotorDirection moveD){
    Order newOrder;
    
    newOrder.floorFrom = floorF;
    newOrder.floorTo = floorT;
    newOrder.moveDirection = moveD;

    return newOrder;
};