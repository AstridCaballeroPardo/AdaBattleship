#pragma once

class BaseState {
  public:
    //Constructor
    BaseState();
    //Destructor
    virtual ~BaseState();

    //member methods
    virtual void enter();
    virtual void exit();
    virtual void update();
    virtual void render();
};