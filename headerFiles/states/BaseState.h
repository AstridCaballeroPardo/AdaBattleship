#pragma once


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
    virtual void update();
    virtual void render();
};