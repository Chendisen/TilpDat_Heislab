#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "Order.h"

struct OrderListEl{
    Order* next;
    Order now;
    Order* prev;
};

class OrderHandler{
    
};