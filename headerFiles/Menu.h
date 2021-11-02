#pragma once

#include <set>

#include "Grid.h"

void menuShipType(std::vector<Ship>& ships);
void shipTextToPrint(int shipType, std::string shipTypeStr, std::string msg);
void menuOrientation();
void manuallySetFleet(Grid& grid);
void getUnplacedShips(Grid& grid, int shipCount, std::vector<int>& unplacedShipsVect, int gridSize, std::set<int>& indexSet);
void automaticallySetFleet(Grid& grid);
std::string menuContinue();
std::string menuTransToPlay();
std::string menuTurn();
std::string menuSetFleet();
std::string menuEndGame();
std::string menuGameType();
std::string menuEntry();
std::string menuShoot();
