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
  Grid& grid1 = *StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = *StateMachine::getInstance()->getGridPlayer2();
  int gridSize = grid1.getSize();

  std::vector<int>& bombedTilesGrid1 = StateMachine::getInstance()->getBombedTilesGrid1();
  std::vector<int>& bombedTilesGrid2 = StateMachine::getInstance()->getBombedTilesGrid1();

  int totalTiles = pow(gridSize, 2);
  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::set<int> indexSetPlayer1 = createSet(totalTiles); 
  int indVal;
  std::set<int> indexSetPlayer2 = createSet(totalTiles); 
  int randomIndex = 0;

  // bool keepPlaying = true;
  bool isNotQuit = true;

  
  
  //take turns until one of the fleets is sunk
  while (grid1.getFleet().getSize() != 0 && grid2.getFleet().getSize() != 0) 
  {
    //player1's turn
    while(true) 
    {   
      //display oponent's board
      std::cout << YELLOW << "\nPlayerA's turn\n" << ENDCOLOUR;
      grid2.renderGrid();

      //ask shoot method. Manual/auto-fired
      input = menuShoot();
      if (input == "1") {
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
            playerShoot(indexSetPlayer2, indVal, gridSize, coordInput, grid2, false);  
            //keep track of bombed tiles         
            bombedTilesGrid2.push_back(indVal); 
            //user ends turn or quits game
            inputMenuTurn = menuTurn();
            if (inputMenuTurn == "0") {
              isNotQuit = false;            
            }                         
            break; 
          }
          else 
          {
            //display message error
            std::cout << "\033[1;31mOut of boundaries, try again.\033[0m\n\n";
          }
        } 

      }
      else 
      {        
        //add time delay
        //add a time delay to improve game's pace.
        usleep(2000000);
        //get random index based on set size
        randomIndex = randomVal(0, totalTiles - 1);

        //check random index is in set(find is O(log n))
        if (indexSetPlayer2.find(randomIndex) != indexSetPlayer2.end())
        {
          playerShoot(indexSetPlayer2, randomIndex, gridSize, coordInput, grid2, true);
          //keep track of bombed tiles         
          bombedTilesGrid2.push_back(randomIndex);                  
          //user ends turn or quits game
          inputMenuTurn = menuTurn();
          if (inputMenuTurn == "0") {
            isNotQuit = false;            
          }                         
          break;  
        } 
      }
    }
    //go in if user wants to keep playing and player2 has ships left
    if (isNotQuit && grid2.getFleet().getSize() != 0) {
      if (grid2.getPlayerType() == "computer")
      {
        //computer's turn
        while(true)
        {  
          //display oponent's board
          std::cout << YELLOW << "\nComputer's turn...\n" << ENDCOLOUR;
          grid1.renderGrid();
          //add time delay
          //add a time delay to improve game's pace.
          usleep(2000000);
          //get random index based on set size
          randomIndex = randomVal(0, totalTiles - 1);

          //check random index is in set(find is O(log n))
          if (indexSetPlayer1.find(randomIndex) != indexSetPlayer1.end())
          {
            playerShoot(indexSetPlayer1, randomIndex, gridSize, coordInput, grid1, true);
            //keep track of bombed tiles         
            bombedTilesGrid1.push_back(randomIndex);                  
            //user ends turn or quits game
            inputMenuTurn = menuTurn();
            if (inputMenuTurn == "0") {
              isNotQuit = false;            
            }                         
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

          //ask shoot method. Manual/auto-fired
          input = menuShoot();
          if (input == "1") {
            msg = "\nEnter row letter, column number(e.g. B4): ";
            input = userInput(msg);
            //validate input
            if(validateInputShootFormat(input))
            {
              coordInput = getParams(input, REGEXSHOOTTILE);
              //validate is within limits
              //calculate index value ((row * length of grid's side) + col)
              indVal = ((coordInput.row - CAPITAL_LETTER)  * gridSize) + coordInput.column;
              
              if(indexSetPlayer1.find(indVal) != indexSetPlayer2.end()) 
              {
                playerShoot(indexSetPlayer1, indVal, gridSize, coordInput,grid1, false);      //keep track of bombed tiles         
                bombedTilesGrid1.push_back(indVal);                  
                //user ends turn or quits game
                inputMenuTurn = menuTurn();
                if (inputMenuTurn == "0") {
                  isNotQuit = false;            
                }                         
                break;  
              }
              else 
              {
                //display message error
                std::cout << "\033[1;31mOut of boundaries, try again.\033[0m\n\n";
              }
            }
          }
          else
          {
            //add time delay
            //add a time delay to improve game's pace.
            usleep(2000000);
            //get random index based on set size
            randomIndex = randomVal(0, totalTiles - 1);

            //check random index is in set(find is O(log n))
            if (indexSetPlayer2.find(randomIndex) != indexSetPlayer2.end())
            {
              playerShoot(indexSetPlayer2, randomIndex, gridSize, coordInput, grid2, true);
              //keep track of bombed tiles         
              bombedTilesGrid2.push_back(randomIndex);                  
              //user ends turn or quits game
              inputMenuTurn = menuTurn();
              if (inputMenuTurn == "0") {
                isNotQuit = false;            
              }                         
              break;  
            } 
          }
        }        
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
    } 
  }
}


void PlayState::exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2)
{
  Grid& grid1 = *StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = *StateMachine::getInstance()->getGridPlayer2();
  //transition back to intro
  //reset ships
  grid1.getFleet().resetFleet(grid1.getGrid());
  //reset bombed empty tiles 
  resetBombedTiles(grid1, bombedTilesGrid1);
  
  //reset ships
  grid2.getFleet().resetFleet(grid2.getGrid());
  //reset bombed empty tiles 
  resetBombedTiles(grid2, bombedTilesGrid2);

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
      StateMachine::getInstance()->change("victory", 2);
    }
  }
}

void PlayState::render(){}