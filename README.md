# Demo video can also be found in [youtube] (https://youtu.be/qvQYAjfMuOA)

# 1. Challenge Outline  
### a. Summary and review of the problem, overall proposed solution. 
The [proposed solution](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/designOverAll.draw) is to implement the **State pattern** to wrap the game. (In case the replit link can't be accessed then find the proposed solution in [GitHub](Documentation/designOverAll.pdf)).

This pattern allows different behaviours depending on the state it is in at a given moment. for example, during the *'setup state'* the *'enter()'* method is all about setting the fleets of both players but when it transitions to *'play state'* the *'enter()'* method is all about shooting. Similarly for the *'exit()'* method, if the game is in the *'setup state'* then to exit it only needs to reset the Fleets; if the game is in the 'play state' then *'exit()'* needs to reset the fleet and also reset the tiles that were bombed.

The state pattern provides a good separation of concerns in terms of what is required in a certain phase of the game. It also, helps to loop through the game efforlestly, for example when a player decides to quit the game, the user is taken to the *'intro state'* where she/he can either start a new game or exit the game completely.

In order to access the game's grids (one grid/board per player) the design also implements the **Singleton pattern**. The grids are instanciated inside the *'state machine'*, so making the *'state machine'* a **Singleton** allows global access to the grids. 

### b. UML style diagram illustrating initial overall solution (linked to 1a) 
see Diagram [here](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/designOverAll.draw)
### c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a,  1b). 
The process started by deciding which classes to implement:
 * Grid
 * Fleet
 * Ship
 * Tile
 
The design of how they relate to each other are [here](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/designOverAll.draw), under the subtitle **'Details!'**

**Testing** was performed during the implementation of the classes that represent the objects of the game, see examples [here](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/testing.md).

Once the objects of the game were in place, the next step was to implement the **State pattern**, for that the following classes were created (see Epic [here](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md)):
* StateMachine: class that can have a number of internal states, known as context[^1].
* BaseState: Abstract class holding the behaviors (virtual methods) that will be inherited by the states fo the game. The vrtual methods are:
  - enter
  - exit
  - update
  - render

* IntroState: child class, that welcomes the player and allows the player exit the game for good.
* SetupState: child class, in this state players set up their fleets.
* PlayState: child class, in this state the players shoot the grid/board of the opponent.
* VictoryState: child class, if human wins the game transitions into this state and render the due congratulations.
* GameOver: child class, if computer wins the game transitions to this state and tells the human that unfortunally she/he has lost.

When the 'SetupState' was being implemented (see [Epic](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md)), there was the realisation that a **Singleton pattern** was needed in order to access the grids in each state, so 'StateMachine" became a **Singleton**.

After that, and during the 'SetupState' work, it was implemented the ability to auto-place ships (see [Epic](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md)).

At this point, there was testing again. Checking that the grids for both players were set up and that validation was in place to prevent wrong inputs from the user.

Next step, implementing the 'PlayState' (see [Epic](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md)), followed by testing.

finally, implementing the 'VictoryState' and 'GameOver'(see [Epic](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md)). If playing 'Two player' version of the game (two humans) then the transition will always be to the 'VictoryState' but if the version played is 'player vs computer' and computer, wins the game transitions to 'GameOver'.

More testing at this point.

Refactoring time, first refactoring 'SetupState' then refactoring 'PlayState'. Lots of testing at each change. Found bugs. Created new bugs. 

The newly created functions were all placed in one place, so next step was to place the functions in better locations. Created new files to hold helper functions for 'PlayState' and 'SetupState'. Test at each change. Found bugs. Created new bugs.

Check whole code. Refactor functions inside 'Grid' class and also helper functions such as 'manuallySetFleet' and 'automaticallySetFleet'.
 
### d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c). e. Initial object-oriented design ideas and planned phased breakdown into smaller tasks (linked to 1d). 
See [Epics](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/Epics.md).

# 2. Development 
### a. Adoption and use of ‘good’ standards (linked to 1a, 1b, 1c). 
- Naming of functions and variables as explicit as possible.
- Comments through out the code.
- Consinstent indentation.
- Refactoring to reduce code, flat arrow code, separation of concerns.
- conserve of system resources by passing by reference.
- regular commits to github.
### b. Phase 1 development: tasks, code review and changes (linked to 1d,1e). 
- Write classes 'Grid', 'Tiile', 'Ship' and 'Fleet'.
- instatiate them, connect them and test them.
- Learn a strategy to refactor. I was taught to take code out of a function and put it at the top of the file, make that code a new function and integarte it to the original code. Then it can be move to another file for example to a helper file.
### c. Phase 2 development: tasks, code review and changes (linked to 1d,1e). 
- Implement the **State Pattern**.
- refactor code.
- Implement **Singleton pattern**.
- refactor code.
- originally use pointers during this phase.

### d. Phase 3 development: tasks, code review and changes (linked to 1d,1e). 
- refactor 'SetupState', the 'enter()' method was long and full of arrow code.
- refactoring introduce bugs, so there was constant testing at each change.

### e. Phase 4 development: tasks, code review and changes (linked to 1d,1e). 
- refactor 'PlayState', the 'enter()' method was long and full of arrow code.
- refactoring introduce bugs, so there was constant testing at each change.

### f. Phase 5 development: tasks, code review and changes (linked to 1d,1e). 
- refactor helper functions.
- create new file to store and reorganise location helper functions. 
- refactoring introduce bugs, so there was constant testing at each change.

### g. Phase 6 development: tasks, code review and changes (linked to 1d,1e). 
- Replace the use of pointers for references, mainly for the Grid instances.
- Add 'delete' pointer related to the 'currentState' attribute inside 'StateMachine' *destructor* to avoid memory leak.
- when instantiating a temporal 'Tile' use smart pointers.

### h. Ensuring quality through testing and resolving bugs (linked to 1a, 1b, 2a, 2b..2c). 
- Testing and debugging during implementation and refactoring.
- The breakpoints during debbuging were commited to github.


### i. Reflection on key design challenges, innovations and how they were solved (with examples). 

Implementing the State pattern was a challenge as it was the first time I used it. However, from examples of game development I researched I felt strongly that this pattern was going to create a good flow for game. 

The first major challenge was to implement the 'states' attribute in the 'StateMachine'. First researching for examples of how the states are stored in the 'StateMachine', many of those I found too complex. I set for using Map, so I could have a key, value pair of information:

```std::map<std::string, BaseState*> states_;```

The next challenge, was to populate the map in the **constructor**'s 'StateMachine'. I took me some time to figure it out and this is the result:
```
StateMachine::StateMachine():gridPlayer1_(), gridPlayer2_()
{
  states_.insert(std::make_pair("intro", new IntroState()));
  states_.insert(std::make_pair("setup", new SetupState()));
  states_.insert(std::make_pair("play", new PlayState()));
  states_.insert(std::make_pair("victory", new VictoryState()));
  states_.insert(std::make_pair("gameover", new GameOverState()));

  currentState = states_.find("intro")->second;   
}
```

Then I went on to implementing the states. However, I soon ran into other problem and it was accessing the grids, which at that point I was creating inside 'IntroState'. This made me realised that their scope was limited to that state and that I was not going to be able to access it from any other state, so I needed to instantiate the grids in the 'StateMachine' instead and make the 'StateMachine' a global variable. 

Then I implemented the *Singleton* pattern for the 'StateMachine' and added the two grids as attributes there.

Another thing that I realised at this point was that the game needed a 'SetupState', originally the states were: *intro, play, victory and gameover*; After this, the states included *setup*.

Once I had the **State and singleton patterns** the game had a good flow and the separation of the game in states makes coding easier as I had to focus on smaller problems. 

# 3. Evaluation 
### a. Analysis with embedded examples of key code refactoring, reuse, smells. 
Below is an example of some of the arrow code I created :scream_cat:

```
void SetupState::enter()
{
  //ask type of game to play
  std::string input;
  std::string msg;
  
  msg = "Select from the menu: \n1. One player vs computer game\n2. Two player game\n3. Quit\n";

  input = userInput(msg);

  if (input == "1") 
  {
    StateMachine::getInstance()->getGridPlayer1()->setPlayerType("human"); 
    StateMachine::getInstance()->getGridPlayer2()->setPlayerType("computer");

    while(true) {
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR; 
      StateMachine::getInstance()->getGridPlayer1()->renderGrid();     
      
      while (true) {
        //if fleet is completed
        if (isFleetCompleted(StateMachine::getInstance()->getGridPlayer1())) 
        {
          //ask what to to next
          input = menuContinue();
          if (input == "1") 
          {
            break;
          }
          else if (input == "2") 
          {
            StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
          }
          else 
          {
            exit();
          }
          
        }

        //if fleet is not completed
        input = menuSetFleet();
        if (input == "1") {
          manuallySetFleet(StateMachine::getInstance()->getGridPlayer1()); 
        }
        else if (input == "2") 
        {
          automaticallySetFleet(StateMachine::getInstance()->getGridPlayer1());
        }
        else if (input == "3") 
        {
          StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
        }
        else {
          exit();
        }
      }
      break;
    }
      
    std::cout << GREEN << "\nComputer placing Fleet...\n\n" << ENDCOLOUR;
    //add a time delay to improve game's pace.
    usleep(2000000);
    automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());        
    
  }  
  else if(input == "2") 
  {
    StateMachine::getInstance()->getGridPlayer1()->setPlayerType("human"); 
    StateMachine::getInstance()->getGridPlayer2()->setPlayerType("human");

      while(true) {
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR;
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer1());

      std::string inputMenuReset = menuContinue();
      //reset
      if (inputMenuReset == "2")
      {    
      StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
      }
      else if(inputMenuReset == "3")
      {
        //auto-place all/remaining ships
        automaticallySetFleet(StateMachine::getInstance()->getGridPlayer1());
      }
      else if(inputMenuReset == "0")
      {
        exit();
      }
      else 
      {
        break;
      }
    }

      while(true) {
      std::cout << YELLOW << "\nPlayerB set your fleet: \n" << ENDCOLOUR;
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer2());

      std::string inputMenuReset = menuContinue();
      //reset
      if (inputMenuReset == "2")
      {    
      StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
      }
      else if(inputMenuReset == "3")
      {
        //auto-place all/remaining ships
        automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());
      }
      else if(inputMenuReset == "0")
      {
        exit();
      }
      else 
      {
        break;
      }
    }       
  }
  else
  {
    exit();
  }
  
  render();
}
```
Function after refactoring :smiley_cat:
```
void SetupState::enter()
{
  char playerLabel = ' ';
  bool isNotQuit = true;
  
  //ask type of game to play
  std::string input;

  input = menuGameType();

  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  
  //set type of players human/computer
  setPlayersType(grid1, grid2, input);
  
  //player vs computer
  if (input == "1") 
  {
    playerLabel ='A';
    playerTurnLoop(grid1, isNotQuit, playerLabel);
    
    if (!isNotQuit) 
    {
      exit();
    }  
    //next player
    else 
    {
      std::cout << GREEN << "\nComputer placing Fleet...\n\n" << ENDCOLOUR;
      //add a time delay to improve game's pace.
      usleep(2000000);
      automaticallySetFleet(grid2);  
      render ();
    }  
  }  
  else if(input == "2") 
  {
    playerLabel ='A';
    playerTurnLoop(grid1, isNotQuit, playerLabel);
    
    if (!isNotQuit) 
    {
      exit();
    }  
    //next player
    else 
    {
      playerLabel ='B';
      playerTurnLoop(grid2, isNotQuit, playerLabel);

      if (!isNotQuit) 
      {
        exit();
      }
      else 
      {
        render ();
      } 
    }   
  }
}
```
There are not while loops anymore! a strategy I found online[^2] is to decompose conditional blocks into separate functions. Another strategy, is to replace conditions with guard clauses instead. Applying this strategies helped to reduce the code, made it more readable and provide functions that can be reuse by other functions.

### b. Implementation and effective use of ‘advanced’ programming principles (with examples). 
As I already mentioned, I implemented the State and Singleton pattern in the design of the game (the design can be found [here](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/designOverAll.draw)).

Implementing the State pattern also was an opportunity to use **inheritance** and **polymorphism**.

For example:

#### Base class
```
//abstract class that will be the base for the 'states' of the game. 'virtual' is what allows polymorphism
class BaseState {
  public:
    //Constructor
    BaseState();
    //Destructor
    virtual ~BaseState();

    //member methods
    virtual void enter();
    virtual void enter(int params);
    virtual void exit();
    virtual void exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2);
    virtual void update();
    virtual void render();
};
```
#### Derived class:
```
class PlayState: public BaseState {
  public:
    //Constructor
    PlayState();
    //Destructor
    ~PlayState();

    //member methods
    void enter();
    void exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2);
    void update();
    void render();  
};
```
I also was able to use function overloading. The base class has two methods called *'enter()'* and two methods called *'exit()'*.


### c. Features showcase and embedded innovations (with examples) - opportunity to ‘highlight’ best bits. d. Improved algorithms – research, design, implementation, and tested confirmation (with examples). e. Reflective review, opportunities to improve and continued professional development.

- Game flows nicely from Introduction to setting up the Fleets to playing,  in particular when the player quits. If the player is setting the Fleet or is playing and decides to quit, the game takes the user to the intro state where the user then can fully exit the game but still has the opportunity to change her/his mind and start a new game.

Example of the code that allows this flow:
```
void SetupState::exit()
{
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  
  // transition back to intro
  grid1.resetFleet();  
  grid2.resetFleet();  
  StateMachine::getInstance()->change("intro"); 
}

void SetupState::update()
{
  //transition to next state
  StateMachine::getInstance()->change("play"); 
}
```

- I feel the game covers a good amount of input validation and allows the users to try again without breaking the game.

Example of validation functions:
```
bool validateInputFormat(std::string str);

bool validateInputShootFormat(std::string str);

bool validateInputMenu(std::string str, std::string regPatt);

bool validateBounds(char row, int column, int gridSize);

bool isManualTargetValid(std::vector<int> vectorResourse, int val);
```

- When autoplacing the ships (all/remaining), the game generates a random target and a random orienattion. I like that if the target is valid but the orientation doesn't have available tiles then it tries using the other orientation, before giving up and trying a new random target.

```
void automaticallySetFleet(Grid& grid) 
{
  ....

    //get random index based on set size
    randomIndex = randomVal(0, totalTiles - 1);    

    //check random index is in set(find is O(log n))
    if (!(indexSet.find(randomIndex) != indexSet.end())) 
    {
      continue;
    }
    // if (indexSet.find(randomIndex) != indexSet.end()){
    availableTiles_++;

    //get random orientation 
    coordInput.orientation = orientationIntToChar(randomVal( 1, 2));

    //check number of tiles available
    availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, indexSet, shipLen);
    if (!(availableTiles_ == shipLen)) 
    {
      //try the other orientation
      availableTiles_ = 1;        
      coordInput.orientation = coordInput.orientation == 'H' ? 'V':'H';

      //check number of tiles available
      availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, indexSet, shipLen);
    }    
    if (!(availableTiles_ == shipLen)) 
    {
      continue;
    }
    //setup and place the ship
    setupPlacingShip(shipLen, coordInput, randomIndex, gridSize, unplacedShipsVect, placedShip, grid, indexSet);        
  }  
} 
```

- Resetting the Tiles was also an interesting one. There are two reset problems depending where you are in the game. If the player is setting the Fleet and decides to quit or reset, the game resets the only the ships. But if the player is in the play state and the user decides to quit then the game resets the ships but it also resets the tiles that were bombed but didn't belong to a Fleet. For that the game keeps track of the shooted tiles, whit this process I am avoiding to check every tile of the grid.

Below is the function that rests tiles that were bombed but don't below to a ship.

```
void Grid::resetBombedTiles(std::vector<int>& bombedTilesGrid)
{
 std::shared_ptr<Tile> tmpTile = std::make_shared<Tile>();
 for (int i = 0; i < bombedTilesGrid.size(); i++)
 {
   //find tile and reset
   //define shipLen, orientation, x and y
   int x =(bombedTilesGrid[i] / size_);
   int y = (bombedTilesGrid[i] % size_);
   //only reset the bombed tiles that didn't belong to ships. There is another reset function that resets the ships wheter they were bombed or not.
   if (grid[x][y].getIcon() == '~' && grid[x][y].getTileState() == 2)
   {
     resetTile(x, y, tmpTile);
   }   
 }
 //empty the vector holding the bombed tiles
 bombedTilesGrid.clear();
}
```

I would have liked to be able to check for memory leaks and to get completely rid of raw pointers.

I also, wanted to implement a strategy for the computer to target ships. I designed the epic but I lacked the time to implement and test it properly. Because of this, I was not able to test the 'GameOver' state. However, because I was able to implement the 'two player' version of the game I was able to test the second grid which is the same one that the computer uses. 

A pleasant surprise when running into bugs was to realise that I was becoming more in tune with my code. I was able to deduce where the issues arose :nerd_face:, which made debugging faster.

I had a lot of fun implementing the State pattern, it was challenging and rewarding. I am looking forward to learn new patterns as they not only provide a strong design but also it is very interesting to see such creative ways of solving problems and learn to identify them.

[^1]: Freeman, E., Robson, E., Sierra, K., & Bates, B. (2020). Head First design patterns. Sebastopol, CA: O'Reilly.
[^2]: https://blog.codinghorror.com/flattening-arrow-code/
