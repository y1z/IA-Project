#pragma once
#include "definitions.h"



class BaseState
{
public:
  virtual ~BaseState() = default;

public:

  /**
  * @brief : controls what happens when the state starts.
  * @param[in] descriptor ;a descriptor for the state.
  * @bug :no known bugs.
  */
  virtual void
  onEnter() = 0;

  /**
  * @brief :  control what happens when exiting the state.
  * @bug :no known bugs.
  */
  virtual void
  onExit() = 0;


  /**
  * @brief : the behavior of each state.
  * @return : the state in which the boid is in now.
  * @bug :no known bugs.
  */
  virtual stateFlags 
  update(float elapsedTime) = 0;

public:
  sBoidPtrAndState* m_actor = nullptr;
  stateFlags m_currentStateFlag;
private:

};

