#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/PlayState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Ship.h"

#include <math.h>

    //Constructor
    PlayState::PlayState():BaseState() {};
    //Destructor
    PlayState::~PlayState(){}

    //member methods
    void PlayState::enter()
    {
      std::string input;
      std::string msg;
      udtCoordInput coordInput;
      int tileTargetState; 
      int x;
      int shipTargetId;
      int gridSize = StateMachine::getInstance()->getGridPlayer1()->getSize();

      int totalTiles = pow(gridSize, 2);
      //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
      std::set<int> indexSetPlayer1 = createSet(totalTiles); 
      int indVal;
      std::set<int> indexSetPlayer2 = createSet(totalTiles); 
      int randomIndex = 0;

      bool keepPlaying = true;

      //take turns
      while (keepPlaying) 
      {
        //player's turn
        while(true) 
        {          
          //display computer's grid
          StateMachine::getInstance()->getGridPlayer2()->renderGrid();

          msg = "\nEnter row letter, column number(e.g. B4): ";
          input = userInput(msg);
          //validate input
          if(validateInputShootFormat(input))
          {
            coordInput = getParams(input, REGEXSHOOTTILE);
            //validate is within limits
            //calculate index value ((row * length of grid's side) + col)
            indVal = ((coordInput.row - CAPITAL_LETTER)  * gridSize) + coordInput.column;
            
            if(indexSetPlayer1.find(indVal) != indexSetPlayer1.end()) 
            {
              //go to targeted tile
              x = letterToInt(coordInput.row);
              tileTargetState = StateMachine::getInstance()->getGridPlayer2()->getGrid()[x][coordInput.column].getTileState();
              //if is part of a ship and has not been boombed
              if (tileTargetState == 1) 
              {
                //Update tile. change tileState and icon
                StateMachine::getInstance()->getGridPlayer2()->getGrid()[x][coordInput.column].setTileState((int)TileState::bombedTile);
                
                //identify ship
                shipTargetId = StateMachine::getInstance()->getGridPlayer2()->getGrid()[x][coordInput.column].getShipId();
                
                //find ship in fleet
                std::vector<Ship>& ships = StateMachine::getInstance()->getGridPlayer2()->getFleet().getFleetVector();              
                Ship& shipTarget = StateMachine::getInstance()->getGridPlayer2()->getFleet().getShip(ships, shipTargetId);              
                if (shipTarget.getShipId() == shipTargetId)
                {
                  //reduce length
                  shipTarget.reduceShipLen();

                  //update fleet if ship is sunk
                  if (shipTarget.getShipLen() == 0)
                  {
                    shipTarget.setIsSunk(true);
                    std::cout << "Ship is sunk!\n";

                    StateMachine::getInstance()->getGridPlayer2()->getFleet().reduceFleetSize();
                    //transition state
                    if (StateMachine::getInstance()->getGridPlayer2()->getFleet().getSize() == 0) 
                    {
                      std::cout << "Fleet is sunk!\n";
                      keepPlaying = false;
                      // break;
                      // update();
                    } else {
                      //display computer's grid
                      StateMachine::getInstance()->getGridPlayer2()->renderGrid();
                      
                    }
                  }
                }
              } else if (tileTargetState == 0) 
              {
                //Update tile. change tileState and icon
                StateMachine::getInstance()->getGridPlayer2()->getGrid()[x][coordInput.column].setTileState((int)TileState::bombedTile);
                StateMachine::getInstance()->getGridPlayer2()->getGrid()[x][coordInput.column].setIcon('-');
                // break;
              }
              //end of player's turn
              //display computer's grid
              StateMachine::getInstance()->getGridPlayer2()->renderGrid();
              break; 
            }
            else 
            {
              //display message error
              std::cout << "\033[1;31mOut of boundaries, try again.\033[0m\n\n";
            }
          }
        }
        

        //computer's turn
        while(true)
        {          
          //display players's grid
          StateMachine::getInstance()->getGridPlayer1()->renderGrid();

          //get random index based on set size
          randomIndex = randomVal(0, totalTiles - 1);

          //check random index is in set(find is O(log n))
          if (indexSetPlayer2.find(randomIndex) != indexSetPlayer2.end())
          {
            coordInput.row = intToLetter((randomIndex / gridSize));
            std::cout << "row: " << randomIndex / gridSize << '\n';
            coordInput.column = (randomIndex % gridSize);

            //go to targeted tile
            x = letterToInt(coordInput.row);
            std::cout << "x: " << x << '\n';
            
            tileTargetState = StateMachine::getInstance()->getGridPlayer1()->getGrid()[x][coordInput.column].getTileState();

            if (tileTargetState == 1) 
            {
              //Update tile. change tileState and icon
              StateMachine::getInstance()->getGridPlayer1()->getGrid()[x][coordInput.column].setTileState((int)TileState::bombedTile);
              
              //identify ship
              shipTargetId = StateMachine::getInstance()->getGridPlayer1()->getGrid()[x][coordInput.column].getShipId();
              
              //find ship in fleet
              std::vector<Ship>& ships = StateMachine::getInstance()->getGridPlayer1()->getFleet().getFleetVector();              
              Ship& shipTarget = StateMachine::getInstance()->getGridPlayer1()->getFleet().getShip(ships, shipTargetId);
              if (shipTarget.getShipId() == shipTargetId)
              {
                //reduce length
                shipTarget.reduceShipLen();

                //update fleet if ship is sunk
                if (shipTarget.getShipLen() == 0)
                {
                  shipTarget.setIsSunk(true);
                  std::cout << "Ship is sunk!\n";

                  StateMachine::getInstance()->getGridPlayer1()->getFleet().reduceFleetSize();
                  //transition state
                  if (StateMachine::getInstance()->getGridPlayer1()->getFleet().getSize() == 0) 
                  {
                    std::cout << "Fleet is sunk!\n";
                    keepPlaying = false;
                    // update();
                  } else {
                    //display computer's grid
                    StateMachine::getInstance()->getGridPlayer1()->renderGrid();
                    // break;
                  }
                }
              }
            } 
            else if (tileTargetState == 0) 
            {
              //Update tile. change tileState and icon
              StateMachine::getInstance()->getGridPlayer1()->getGrid()[x][coordInput.column].setTileState((int)TileState::bombedTile);
              StateMachine::getInstance()->getGridPlayer1()->getGrid()[x][coordInput.column].setIcon('-');
              // break;
            }
            //remove tile's index from set so computer won't select it again
            removeTarjetSet(randomIndex, indexSetPlayer2);

            //end of computer's turn
            break;
          }
        }
      }
      update();
    }


    void PlayState::exit(){};
    void PlayState::update()
    {
      //if oponent fleet sunk player wins   
      if (StateMachine::getInstance()->getGridPlayer2()->getFleet().getSize() == 0) 
      {
        StateMachine::getInstance()->change("victory"); 

      }  
      //if player fleet sunk player looses  
      else if (StateMachine::getInstance()->getGridPlayer1()->getFleet().getSize() == 0)
      {
        StateMachine::getInstance()->change("gameover");
      }
    }
    void PlayState::render()
    {
      //render both grids
      
      //ask if player wants to play again or exit

    }