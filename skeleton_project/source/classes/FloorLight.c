#include "FloorLight.h"

FloorLight makeFloorLight(){
    FloorLight newFloorLight;
    newFloorLight.currentLight = NONE;

    return newFloorLight;
}

void floorLightsOn(Floor currentFloor, FloorLight *floorLightPtr){
    floorLightPtr->currentLight = currentFloor;
    elevio_floorIndicator((int)currentFloor);
}
