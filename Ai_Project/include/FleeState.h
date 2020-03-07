#pragma once
#include "BaseState.h"


  /**
  * @brief : controls a boid that is fleeing.
  * @bug : no known bugs.
  */
class FleeState :
  public BaseState
{
public:
  FleeState();
  ~FleeState() = default;
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
    * @brief : choses a random behavior when a boid is close enough.
    * @return : the state in which the boid is in now.
    * @bug :no known bugs.
    */
  stateFlags
  update(float elapsedTime) override;



};

