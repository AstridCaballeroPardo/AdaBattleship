#include "../../headerFiles/states/BaseState.h"


    //Constructor
    BaseState::BaseState() {}
    //Destructor
    BaseState::~BaseState(){}

    //member methods
    void BaseState::enter(){}
    void BaseState::enter(int params){}
    void BaseState::exit(){}
    void BaseState::exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2){}
    void BaseState::update(){}
    void BaseState::render(){}
