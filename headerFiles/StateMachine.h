#pragma once



class StateMachine {
  public:
  //constructor
  StateMachine(std::string states);

  //StateMachine member methods
  void change();
  void update();
  void render();