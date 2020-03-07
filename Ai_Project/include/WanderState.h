#pragma once
#include "BaseState.h"
#include <vector>


class WanderState :
  public BaseState
{
public:
  WanderState();
  ~WanderState() = default;

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
  * @brief : the boid move in a random direction for some time.
  * @return : the state in which the boid is in now.
  * @bug :no known bugs.
  */
  stateFlags
  update(float elapsedTime) override;

private:

  /**
  * @brief : finds out if the state already has an ID from a 
  * boid.
  * @bug : no known bugs.
  */
  bool
  checkForID(BoidPtr boid);
  
  /**
  * @brief : add a id and resulting force. 
  * @bug : no known bugs.
  */
  void 
  addForceAndID(enVector2& force, uint32_t newID);

  /**
  * @return: a force that belongs to a particular boid.
  * @bug : no known bugs.
  */
  enVector2
  findForceByID(uint32_t newID)const;

  /**
  * @brief : remove 
  * @bug : no known bugs.
  */
  void
  removeForceByID(uint32_t newID);

  /**
  * @brief : keeps track of which force belong to which vector.
  */
  std::vector<VectorAndID>  m_idsAndForces;
};

