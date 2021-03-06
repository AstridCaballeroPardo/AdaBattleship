
#include <math.h>
#include <unistd.h>

#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/PlayState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/PlayHelper.h"

//Constructor
PlayState::PlayState():BaseState() {}
//Destructor
PlayState::~PlayState(){}

//member methods
void PlayState::enter()
{
  bool hide = true;
  std::string input;
  std::string msg;
  udtCoordInput coordInput;  
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  int gridSize = grid1.getSize();
  int totalTiles = pow(gridSize, 2);

  std::vector<int>& bombedTilesGrid1 = StateMachine::getInstance()->getBombedTilesGrid1();
  std::vector<int>& bombedTilesGrid2 = StateMachine::getInstance()->getBombedTilesGrid2();
  
  //create vector with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::vector<int> indexVecPlayer1 = vectorResourse(totalTiles);   
  std::vector<int> indexVecPlayer2 = vectorResourse(totalTiles); 
  int indVal = -1;
  int randomIndex = -1; 
  // int valAtRandomIndx = -1;  
  bool isNotQuit = true;
  char playerLabel = ' ';
  
  //take turns until one of the fleets is sunk
  while (grid1.getFleet().getSize() != 0 && grid2.getFleet().getSize() != 0) 
  {
    //player1's turn   
    playerLabel = 'A'; 
    
    playerShootTurn(grid2, indexVecPlayer2, bombedTilesGrid2, playerLabel, coordInput, indVal, gridSize, isNotQuit, hide);
    
    //go in if user wants to keep playing and player2 has ships left
    if (isNotQuit && grid2.getFleet().getSize() != 0) 
    {
      if (grid2.getPlayerType() == "computer")
      {
          //display oponent's board
          std::cout << YELLOW << "\nComputer's turn...\n" << ENDCOLOUR;
          grid1.renderGrid(hide);
          //add time delay
          //add a time delay to improve game's pace.
          usleep(2000000);
           
          autoFire(indexVecPlayer1, gridSize, coordInput, grid1, bombedTilesGrid1, isNotQuit, hide); 
      }
      else 
      {
        //player2's turn         
        //display oponent's board
        playerLabel = 'B'; 
       
        playerShootTurn(grid1, indexVecPlayer1, bombedTilesGrid1, playerLabel, coordInput, indVal, gridSize, isNotQuit, hide);
      }    
    }
    if (!isNotQuit) 
    {
      exit(bombedTilesGrid1, bombedTilesGrid2); 
      // break;     
    }
   // transition state
    else 
    {
      update();
      // break;
    } 
  }
}


void PlayState::exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2)
{
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  //transition back to intro
  //reset ships
  grid1.resetFleet();
  //reset bombed empty tiles 
  grid1.resetBombedTiles(bombedTilesGrid1);
  
  //reset ships
  grid2.resetFleet();
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