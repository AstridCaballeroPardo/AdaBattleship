#pragma once

#include <vector>

void playerShoot(std::vector<int>& indexVectPlayer, int valIndex, int gridSize, udtCoordInput coordInput, Grid& gridPlayer, bool isAutofired, bool hide);

void autoFire(std::vector<int>& indexVecPlayer, int gridSize, udtCoordInput coordInput, Grid& grid, std::vector<int>& bombedTilesGrid, bool& isNotQuit, bool hide); 

void manualShoot(udtCoordInput coordInput, int indVal, int gridSize, std::vector<int>& indexVecPlayer, std::vector<int>& bombedTilesGrid, bool& isNotQuit, Grid& grid, bool hide); 

void playerShootTurn(Grid& grid, std::vector<int>& indexVecPlayer, std::vector<int>& bombedTilesGrid, char playerLabel, udtCoordInput coordInput, int indVal, int gridSize, bool& isNotQuit, bool hide); 