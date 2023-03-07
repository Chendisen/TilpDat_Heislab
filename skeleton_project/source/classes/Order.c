#include "Order.h"


Order makeOrder(ButtonType buttonType, Floor floor){
    Order newOrder;
    newOrder.buttonType = buttonType;
    newOrder.floor = floor;

    return newOrder;
};

void lightsOn(Order* order){
    elevio_buttonLamp((int)(order->floor), order->buttonType, 1);
}

void lightsOff(Order* order){
    elevio_buttonLamp((int)(order->floor), order->buttonType, 0);
} 