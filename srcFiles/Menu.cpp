#include <iostream>

#include "../headerFiles/Menu.h"

void menuShipType(){
  std::cout << "\nShip options: \n";
  std::cout << "ID TYPE         SIZE\n";
  std::cout << "0. Carrier        5\n";
  std::cout << "1. Battleship     4\n";
  std::cout << "2. Destroyer      3\n";
  std::cout << "3. Submarine      3\n";
  std::cout << "4. Patrol Boat    2\n";
}

void menuOrientation(){
  std::cout << "\nOrientation options: \n";
  std::cout << "V. Vertical\n";
  std::cout << "H. Horizontal\n";
}