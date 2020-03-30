#include "BaseState.h"
#include <array>


class cFSM
{
public:
  cFSM();
  ~cFSM();
public:

  /**
  * @brief : used to gather all the resource the FSM needs.
  * @bug : no known bugs.
  */
  bool 
  init(std::vector<Boid>& boidsContainer,
       Boid* ptrToTarget = nullptr);

  /**
  * @brief : cases every boid to perform there own behavior.
  * @bug : no known bugs.
  */
  void
  executeMachine(float elapsedTime);


private:

  /**
  * @brief : make sure every boid has the appropriate arguments 
  * before executing some state.
  * @bug : no known bugs.
  */
  void
  assignArgsForBehavior();

  /**
  * @brief : get the data necessary from the boid for the 
  *         FSM to function.
  * @bug : no known bugs.
  */
  bool 
  extractBoidData(std::vector<Boid>& boidsContainer);

  /**
  * @brief : starts each individual instance of each state.
  * @bug : no known bugs.
  */
  bool
  initStates();

  /**
  * @brief ; initializes all the default for the arguments of the 
  * state machine.
  * @bug : no known bugs.
  */
  bool 
  initArgsForStates(Boid* ptrToTarget = nullptr);


private:
  /**
  * @brief : keeps track of how many state there are.
  */
  constexpr static int32_t c_AmountOfStates = (int32_t)stateFlags::SIZE;

public:

  /**
  * @brief : for when a behavior needs some target
  */
  Boid* 
  m_pTarget = nullptr;

private:
  /**
  * @brief : a pointer to a instance of each state.
  */
  std::array<BaseState*,c_AmountOfStates> m_StateContainer;

  /**
  * @brief : parameters for when a boid is in the seek state.
  */
  seekStateArgs m_seekArguments;

  /**
  * @brief : parameters for when a boid is in the idle state.
  */
  idleStateArgs m_idleStateArguments;

  /**
  * @brief : parameters for when a boid is in the Flee state.
  */
  fleeStateArgs m_fleeStateArguments;

  /**
  * @brief : parameters for when a boid is in the Wander state.
  */
  wanderStateArgs m_wanderStateArguments;

  /**
  * @brief : all the boids the state machine will control.
  */
  std::vector<sBoidPtrAndState> m_boidsAndState;
};


