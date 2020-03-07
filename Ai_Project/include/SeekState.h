#pragma once
#include "BaseState.h"

class SeekState : public BaseState
{
public: 
  SeekState();
  ~SeekState() = default;
public:

  void
  onEnter() override;

    /**
    * @brief :control what happens when exiting the state.
    * @bug :no known bugs.
    */
  void
  onExit()override;


    /**
    * @brief : the behavior of each state.
    * @return : the state in which the boid is in now.
    * @bug :no known bugs.
    */
  stateFlags
  update(float elapsedTime) override;
  
public:

};

