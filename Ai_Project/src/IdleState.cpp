#include "..\include\IdleState.h"
#include "helper.h"


IdleState::IdleState()
{
  m_currentStateFlag = stateFlags::idle;
}

void
IdleState::onEnter()
{
  LOG_MSG(" entered idle state ");
  m_actor->hasEntered = true;
}

void 
IdleState::onExit()
{
  m_actor->hasEntered = false;
  m_actor->ptrToStateDescriptor = nullptr;
}

stateFlags 
IdleState::update(float elapsedTime)
{
  idleStateArgs* ptrDesc = static_cast<idleStateArgs*>(m_actor->ptrToStateDescriptor);
  BoidPtr ptrToBoid = m_actor->ptrToBoid;

  for( sBoidPtrAndState& possibleTargets : *ptrDesc->m_boids )
  {
    bool const isInRadius = ptrToBoid->getDistanceTo(*possibleTargets.ptrToBoid) <= ptrDesc->m_radiusUtilStateChange;
    if( isInRadius ) 
    {
      int32_t const randNum = sfHelp::RandIntRange(0, (int32_t)stateFlags::SIZE - 1);
      LOG_MSG( randNum );
      m_actor->boidState = (stateFlags)randNum;
    }

  }

  return  m_actor->boidState;
}
