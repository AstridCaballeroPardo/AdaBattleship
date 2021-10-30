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
  std::string inputMenuTurn;
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
    // if fleet is sunk
    if (!keepPlaying) 
    {
      break;
    }

    //user ends turn or quits game
    inputMenuTurn = menuTurn();

    if (inputMenuTurn == "0") {
      exit();
    }
    
    if (StateMachine::getInstance()->getGridPlayer2()->getPlayerType() == "computer")
    {
      //computer's turn
      while(true)
      {  
        //display oponent's board
        std::cout << YELLOW << "\nComputer's turn...\n" << ENDCOLOUR;
        StateMachine::getInstance()->getGridPlayer1()->renderGrid();
        //add time delay
        //add a time delay to improve game's pace.
        usleep(2000000);
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
        StateMachine::getInstance()->getGridPlayer1()->renderGrid();

        msg = "\nEnter row letter, column number(e.g. B4): ";
        input = userInput(msg);
        //validate input
        if(validateInputShootFormat(input))
        {
          coordInput = getParams(input, REGEXSHOOTTILE);
          //validate is within limits
          //calculate index value ((row * length of grid's side) + col)
          indVal = ((coordInput.row - CAPITAL_LETTER)  * gridSize) + coordInput.column;
          
          if(indexSetPlayer2.find(indVal) != indexSetPlayer2.end()) 
          {
            playerShoot(indexSetPlayer2, indVal, gridSize, coordInput, keepPlaying, StateMachine::getInstance()->getGridPlayer1());             
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
    // if fleet is sunk
    if (!keepPlaying) 
    {
      break;
    }
    
    //user ends turn or quits game
    inputMenuTurn = menuTurn();
    
    if (inputMenuTurn == "0") {
      exit();
    }
  }
  //transition state
  update();
}


void PlayState::exit()
{
  //transition back to intro
  StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
  
  StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());

  StateMachine::getInstance()->change("intro"); 
};

void PlayState::update()
{
  // check if grid2 is computer
  if (StateMachine::getInstance()->getGridPlayer2()->getPlayerType() == "computer") 
  {
    //if player1 wins  
    if (StateMachine::getInstance()->getGridPlayer2()->getFleet().getSize() == 0) 
    {
      StateMachine::getInstance()->change("victory", 1); 

    }  
    //if computer wins  
    else if (StateMachine::getInstance()->getGridPlayer1()->getFleet().getSize() == 0)
    {
      StateMachine::getInstance()->change("gameover");
    }
  }
  else 
  {
    //if player1 wins  
    if (StateMachine::getInstance()->getGridPlayer2()->getFleet().getSize() == 0) 
    {
      StateMachine::getInstance()->change("victory", 1); 

    }  
    //if computer wins  
    else if (StateMachine::getInstance()->getGridPlayer1()->getFleet().getSize() == 0)
    {
      StateMachine::getInstance()->change("vistory", 2);
    }
  }
  
  
}

void PlayState::render(){}