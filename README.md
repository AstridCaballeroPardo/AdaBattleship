# 1. Challenge Outline  
### a. Summary and review of the problem, overall proposed solution. 
The [proposed solution](https://replit.com/@AstridCaballero/AdaBattleship#Documentation/designOverAll.draw) is to implement the **State pattern** to wrap the game. 

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


### b. Implementation and effective use of ‘advanced’ programming principles (with examples). 
### c. Features showcase and embedded innovations (with examples) - opportunity to ‘highlight’ best bits. d. Improved algorithms – research, design, implementation, and tested confirmation (with examples). e. Reflective review, opportunities to improve and continued professional development.



[^1]: Head First Design Patterns, second Edition page 406. 