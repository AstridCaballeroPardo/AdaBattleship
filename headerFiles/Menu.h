#pragma once

#include "Grid.h"

void menuShipType(std::vector<Ship>& ships);
void shipTextToPrint(int shipType, std::string shipTypeStr, std::string msg);
void menuOrientation();
void manuallySetFleet(Grid* grid);
void automaticallySetFleet(Grid* grid);
