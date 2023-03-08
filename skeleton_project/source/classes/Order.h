#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../driver/elevio.h"

typedef struct {
    ButtonType buttonType;
    Floor floor;

}Order;


Order makeOrder(ButtonType buttonType, Floor floor);

void lightsOn(Order* order);
void lightsOff(Order* order); 