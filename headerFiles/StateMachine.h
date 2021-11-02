#pragma once

#include <iostream>
#include <map>

#include "Grid.h"
#include "states/BaseState.h"

//StateMachine class Points at something that is active (active state). Using this class to implement the State Pattern
class StateMachine {
  //StateMachine class is created using the Singleton pattern
  private:
    //Constructor
    StateMachine();
    static StateMachine* inst_; 
  
  protected:
    std::map<std::string, BaseState*> states_;
    BaseState* currentState = nullptr;
    // Grid* gridPlayer1_ = nullptr;
    // Grid* gridPlayer2_ = nullptr;
    std::vector<int> bombedTilesGrid1_;
    std::vector<int> bombedTilesGrid2_;
    Grid gridPlayer1_;
    Grid gridPlayer2_;
    
    
  public:
    
    StateMachine(StateMachine &other) = delete; 
    void operator = (const StateMachine &) = delete; 
    
    //Destructor
    ~StateMachine();

    static StateMachine *getInstance();
    
    //getters
    Grid& getGridPlayer1()  
    {
        return gridPlayer1_;
    }

    Grid& getGridPlayer2()  
    {
        return gridPlayer2_;
    }

    std::vector<int>& getBombedTilesGrid1() {
      return bombedTilesGrid1_;
    }

    std::vector<int>& getBombedTilesGrid2() {
      return bombedTilesGrid2_;
    }
    
    //StateMachine member methods
    void change(std::string state);
    void change(std::string state, int params);
    void update();
    void render();
    
};