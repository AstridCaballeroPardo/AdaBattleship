#pragma once

#include <set>

#include "Grid.h"

void menuShipType(std::vector<Ship>& ships);
void shipTextToPrint(int shipType, std::string shipTypeStr, std::string msg);
void menuOrientation();
std::string menuContinue();
std::string menuTransToPlay();
std::string menuTurn();
std::string menuSetFleet();
std::string menuEndGame();
std::string menuGameType();
std::string menuEntry();
std::string menuShoot();
