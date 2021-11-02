#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/PlayState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Ship.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Menu.h"

#include <math.h>
#include <unistd.h>

//refactoring

//Constructor
PlayState::PlayState():BaseState() {}
//Destructor
PlayState::~PlayState(){}

//member methods
void PlayState::enter()
{
  std::string input;
  std::string msg;
  udtCoordInput coordInput;  
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  int gridSize = grid1.getSize();
  int totalTiles = pow(gridSize, 2);

  std::vector<int>& bombedTilesGrid1 = StateMachine::getInstance()->getBombedTilesGrid1();
  std::vector<int>& bombedTilesGrid2 = StateMachine::getInstance()->getBombedTilesGrid1();
  
  //create vector with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::vector<int> indexVecPlayer1 = vectorResourse(totalTiles);   
  std::vector<int> indexVecPlayer2 = vectorResourse(totalTiles); 
  int indVal = -1;
  int randomIndex = -1; 
  // int valAtRandomIndx = -1;  
  bool isNotQuit = true;
  
  //take turns until one of the fleets is sunk
  while (grid1.getFleet().getSize() != 0 && grid2.getFleet().getSize() != 0) 
  {
    //player1's turn    
    //display oponent's board
    std::cout << YELLOW << "\nPlayerA's turn\n" << ENDCOLOUR;
    grid2.renderGrid();

    //ask shoot method. Manual/auto-fired
    input = menuShoot();
    if (input == "1") {      
      manualShoot(coordInput, indVal, gridSize, indexVecPlayer2, bombedTilesGrid2, isNotQuit, grid2); 
    }
    //autofire
    else 
    {        
      //add time delay
      //add a time delay to improve game's pace.
      usleep(2000000);
      
      autoFire(indexVecPlayer2, gridSize, coordInput, grid2, bombedTilesGrid2, isNotQuit);
    }
    
    //go in if user wants to keep playing and player2 has ships left
    if (isNotQuit && grid2.getFleet().getSize() != 0) {
      if (grid2.getPlayerType() == "computer")
      {
        //computer's turn
        // while(true)
        // {  
          //display oponent's board
          std::cout << YELLOW << "\nComputer's turn...\n" << ENDCOLOUR;
          grid1.renderGrid();
          //add time delay
          //add a time delay to improve game's pace.
          usleep(2000000);
           
          autoFire(indexVecPlayer1, gridSize, coordInput, grid1, bombedTilesGrid1, isNotQuit); 
        //   break;        
        // }              
      }
      else 
      {
        //player2's turn         
        //display oponent's board
        std::cout << YELLOW << "\nPlayerB's turn\n" << ENDCOLOUR;
        grid1.renderGrid();

        //ask shoot method. Manual/auto-fired
        input = menuShoot();
        if (input == "1") {
            manualShoot(coordInput, indVal, gridSize, indexVecPlayer1, bombedTilesGrid1, isNotQuit, grid1); 
        }
        else
        {
          //add time delay
          //add a time delay to improve game's pace.
          usleep(2000000);
          
          autoFire(indexVecPlayer1, gridSize, coordInput, grid1, bombedTilesGrid1, isNotQuit);  
        }
      }    
    }
    if (!isNotQuit) 
    {
      exit(bombedTilesGrid1, bombedTilesGrid2);      
    }
   // transition state
    else 
    {
      update();
    } 
  }
}


void PlayState::exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2)
{
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  //transition back to intro
  //reset ships
  grid1.getFleet().resetFleet(grid1.getGrid());
  //reset bombed empty tiles 
  grid1.resetBombedTiles(bombedTilesGrid1);
  
  //reset ships
  grid2.getFleet().resetFleet(grid2.getGrid());
  //reset bombed empty tiles 
  grid2.resetBombedTiles(bombedTilesGrid2);

  StateMachine::getInstance()->change("intro"); 
};

void PlayState::update()
{
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  
  // check if grid2 is computer
  if (grid2.getPlayerType() == "computer") 
  {
    //if player1 wins  
    if (grid2.getFleet().getSize() == 0) 
    {
      StateMachine::getInstance()->change("victory", 1); 

    }  
    //if computer wins  
    else if (grid1.getFleet().getSize() == 0)
    {
      StateMachine::getInstance()->change("gameover");
    }
  }
  else 
  {
    //if player1 wins  
    if (grid2.getFleet().getSize() == 0) 
    {
      StateMachine::getInstance()->change("victory", 1); 

    }  
    //if computer wins  
    else if (grid1.getFleet().getSize() == 0)
    {
      StateMachine::getInstance()->change("victory", 2);
    }
  }
}

void PlayState::render(){}