#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <random>
#include <math.h> 
#include <string>
#include <algorithm>
#include <set>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/Tile.h"
#include "headerFiles/Ship.h"
#include "headerFiles/Fleet.h"
#include "headerFiles/Utility.h"
#include "headerFiles/Menu.h"


int main() 
{  
  Grid grid;   
  
  // manuallySetFleet(grid);

  grid.renderGrid();
  std::random_device ramdomDev;

  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::set<int> index;
  
  int totalTiles = pow(grid.getSize(), 2);
  for (int i = 0; i < totalTiles; i++) {
    index.insert(i);
  }
  //print index set
  for (int const& ind : index)
    {
        std::cout << ind << ' ';
    }  
  std::cout << '\n';
  
  //fleet size
  int shipCount = grid.getFleet().getSize();
  std::cout << "number of ships: " << shipCount << '\n';

  udtCoordInput coordInput;
  std::string input;
  int randomIndex = 0;
  int randomOrientation = 0;
  char orientation = ' ';   
  int gridSize = grid.getSize();
  int len = 0;
  int availableTiles = 0;

  //main loop to place the ships
  while (shipCount != 0) {
    std::cout << "start"<< '\n';
    len = calcShipLength(shipCount); 
    availableTiles = 0;
    //get random index based on set size    
    std::mt19937 rng(ramdomDev());
    std::uniform_int_distribution<std::mt19937::result_type> distIndex(0,totalTiles - 1);

    randomIndex = distIndex(rng);
    std::cout << "random index: " << randomIndex << std::endl;
    //check random index is in set(find is O(log n))
    if (index.find(randomIndex) != index.end()){
      availableTiles++;

      //get random orientation
      std::uniform_int_distribution<std::mt19937::result_type> distOrientation(1,2);

      randomOrientation = distOrientation(rng);
      std::cout << "random orientation: " << randomOrientation << std::endl;
      switch(randomOrientation) {
          case 1: 
            orientation = 'V';
            break;
          case 2:
            orientation = 'H';
            break;               
        }
      //check the indexes that will build the ship are in set(e.g: c3 5 v --> 12, 17)
      if (orientation == 'V') {      
        for (int i = randomIndex + gridSize, j = 1; j < len; i+=gridSize, j++) {        
          if (index.find(i) != index.end()) {
              availableTiles++;
          } else {
            break;
          }
        }
      } else {
        for (int i = randomIndex + 1, j = 1; j < len; i++, j++) {  
          //calculate row values to make sure elements belong to the same row
          char xRandom = intToLetter((randomIndex / gridSize));
          char xNext = intToLetter((i / gridSize));

          if (index.find(i) != index.end() && xRandom == xNext ) {
              availableTiles++;
          }
        }
      }

      //setup the ship
      if (availableTiles == len) {        
        char x = intToLetter((randomIndex / gridSize));
        int y = (randomIndex % gridSize) + 1;

        std::cout << "x: " << x << '\n';
        std::cout << "y: " << y << '\n';       
        input = x + std::to_string(y) + " " + std::to_string(shipCount) + orientation;
        std::cout << "input: " << input << '\n';

        //parse input        
        coordInput = getParams(input, grid);
      
        //update grid with player's input                       
        if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation)) {
          //keep track of placed ships to know when fleet is completed
          shipCount --; 

          // remove values from set(the one with values from 0 to GRID_SIZE)              
          if (orientation == 'V') {      
            for (int i = randomIndex, j = 0; j < len; i+=gridSize, j++) {       
              index.erase(i);
            }
          } else {
            for (int i = randomIndex, j = 0; j < len; i++, j++) {        
            index.erase(i);
            }
          }
          //print index set after removing elements
          std::cout << "size of index set: " << index.size() << '\n';
          for (int const& ind : index){
              std::cout << ind << ' ';
          } 
          std::cout << "end " << '\n';
        }
      } else {
        //display message error
        std::cout << "\033[1;31mOut of boundaries! try again.\033[0m\n\n";
      }
    }
  }
    
  grid.renderGrid();
  return 0;
}