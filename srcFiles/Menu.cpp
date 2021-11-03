#include <iostream>
#include <ostream>
#include <math.h> 
#include <vector>
#include <iomanip>
#include <string>
#include <numeric>
#include <algorithm>

#include "../headerFiles/Menu.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Validation.h"

void shipTextToPrint(int shipType, std::string shipTypeStr, std::string msg)
{
  std::cout << std::setfill(' ') << std::setw(2) << shipType << "  " << std::setw(11) << shipTypeStr << "  " << std::setw(4)  << calcShipLength(shipType) << "  " <<  msg;
}

std::string getMsg(std::vector<Ship>& ships, int i)
{
  std::string msg;
  for (int j = 0; j < ships.size(); j++) {
      if (ships[j].getShipType() == i) {
        if(!ships[j].getIsSunk()){
          msg = "placed\n";
          break;
        }
        else {
          msg = "sunk\n";
          break;
        }
      }
      else {
        msg = "not placed\n";
      }
    }
    return msg;
}

void menuShipType(std::vector<Ship>& ships) {
  std::cout << "\nShip options: \n";
  //print headers
  std::cout << std::setfill(' ') << std::setw(2) << "ID" << "  " << std::setw(11) << "TYPE    "  << "  " << std::setw(4) << "SIZE" << "  " << "STATE\n";
  
  for (int i = 1; i <= ships.size(); i++) 
  {
    std::string shipTypeStr = getStringForEnum(i);
    //find the ship with shipType == i
    std::string msg = getMsg(ships, i); 
    
    shipTextToPrint(i, shipTypeStr, msg);
  }
}

void menuOrientation()
{
  std::cout << "\nOrientation options: \n";
  std::cout << "V. Vertical\n";
  std::cout << "H. Horizontal\n";
}

std::string menuContinue()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENURESET))
  {
    std::string msg = "\nSelect:\n1.continue\n2.reset\n0.quit\n";
    input = userInput(msg);
  }
  
  return input;
}

std::string menuTransToPlay()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTRANSTOPLAY))
  {
  std::string msg = "\nReady to play?:\n1.OK\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}

std::string menuTurn()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTURN))
  {
  std::string msg = "\nSelect:\n1.End turn\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}

std::string menuSetFleet()
{
   std::string input = " ";
    while(!validateInputMenu(input, MENUSETMODE))
    {
    std::string msg = "\n1.Manually\n2.Auto-place\n";
    input = userInput(msg);
    }
    return input;
}


std::string menuEndGame()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTURN))
  {
  std::string msg = "\npress:\n1.start new game\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}


std::string menuGameType()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENURESET))
  {
    std::cout << YELLOW << "\n\nLet's play :)\n" << ENDCOLOUR;
    std::string msg = "\n\nSelect from the menu: \n1. One player vs computer game\n2. Two player game\n0. Quit\n";
    input = userInput(msg);
  }
  return input;
}


std::string menuEntry()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUENTRY))
  {
    std::cout << YELLOW << "\n\nWelcome to AdaShip!\n\n" << ENDCOLOUR;
    std::string msg = "Select:\n1.Start\n0.Exit game\n";
    input = userInput(msg);
  }
  return input;
}

std::string menuShoot()
{
   std::string input = " ";
    while(!validateInputMenu(input, MENUSETMODE))
    {
    std::string msg = "\n1.Manually\n2.Auto-fire\n";
    input = userInput(msg);
    }
    return input;
}