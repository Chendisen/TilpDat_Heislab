#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_DOWN      = 0,
    BUTTON_HALL_UP    = 1,
    BUTTON_CAB          = 2
} ButtonType;

typedef enum {
    FALSE   = 0,
    TRUE    = 1
} Bool;

typedef enum {
    NONE = -1, 
    FIRST = 0,
    SECOND = 1, 
    THIRD = 2, 
    FOURTH = 3
} Floor;

#define DOOR_TIME 3



void elevio_init(void);

void elevio_motorDirection(MotorDirection dirn);
void elevio_buttonLamp(int floor, ButtonType button, int value);
void elevio_floorIndicator(int floor);
void elevio_doorOpenLamp(int value);
void elevio_stopLamp(int value);

int elevio_callButton(int floor, ButtonType button);
int elevio_floorSensor(void);
int elevio_stopButton(void);
int elevio_obstruction(void);

