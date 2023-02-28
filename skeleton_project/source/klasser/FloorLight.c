#include "FloorLight.h"

FloorLight makeFloorLight(Floor currentFloor){
    FloorLight newFloorLight;
    newFloorLight.currentLight = currentFloor;

    return newFloorLight;
}

void floorLightsOn(Floor currentFloor, FloorLight *floorLightPtr){
    floorLightPtr->currentLight = currentFloor;
    elevio_floorIndicator((int)currentFloor);
}
