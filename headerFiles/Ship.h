#pragma once

#include <vector>
#include <string>

#include "constants.h"

class Ship {
  private:
    std::vector<int> ship;
    int x; // will be the numeric header
    int y; // will be the letter turn to int
    char orientation; // v - for vertical, h - for horizontal

  public:
  //constructor
  Ship();  

  //Grid member methods
  void createShip();
}