#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/PlayState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Ship.h"
#include "../../headerFiles/Grid.h"

#include <math.h>

//refactoring

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
    //player1's turn
    while(true) 
    {   
      //display oponent's board
      std::cout << YELLOW << "\nPlayerA's turn\n" << ENDCOLOUR;
      // StateMachine::getInstance()->getGridPlayer2()->renderGrid();

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
          playerShoot(indexSetPlayer1, indVal, gridSize, coordInput, keepPlaying, StateMachine::getInstance()->getGridPlayer2());             
          break; 
        }
        else 
        {
          //display message error
          std::cout << "\033[1;31mOut of boundaries, try again.\033[0m\n\n";
        }
      }
    }
    
    if (!isHuman())
    {
      //computer's turn
      while(true)
      {  
        //display oponent's board
        std::cout << YELLOW << "\nComputer's turn\n" << ENDCOLOUR;
        //get random index based on set size
        randomIndex = randomVal(0, totalTiles - 1);

        //check random index is in set(find is O(log n))
        if (indexSetPlayer2.find(randomIndex) != indexSetPlayer2.end())
        {
          playerShoot(indexSetPlayer2, randomIndex, gridSize, coordInput, keepPlaying, StateMachine::getInstance()->getGridPlayer1()); 
          break;
        }
      }
    }
    else 
    {
      //player2's turn
      while(true) 
      {   
        //display oponent's board
        std::cout << YELLOW << "\nPlayerB's turn\n" << ENDCOLOUR;
        // StateMachine::getInstance()->getGridPlayer2()->renderGrid();

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
            playerShoot(indexSetPlayer1, indVal, gridSize, coordInput, keepPlaying, StateMachine::getInstance()->getGridPlayer2());             
            break; 
          }
          else 
          {
            //display message error
            std::cout << "\033[1;31mOut of boundaries, try again.\033[0m\n\n";
          }
        }
      }

    }
    
  }
  //transition state
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
  
}