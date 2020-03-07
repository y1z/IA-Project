#include "FleeState.h"
#include "..\include\FleeState.h"

FleeState::FleeState()
{
  m_currentStateFlag = stateFlags::flee;
}

void
FleeState::onEnter()
{

  LOG_MSG(" entered flee state ");
  m_actor->hasEntered = true;

}

void
FleeState::onExit()
{

  LOG_MSG(" exited  flee state ");
  m_actor->hasEntered = false;
  m_actor->ptrToStateDescriptor = nullptr;
}

stateFlags
FleeState::update(float elapsedTime)
{
  fleeStateArgs* ptrDesc = static_cast<fleeStateArgs*> (m_actor->ptrToStateDescriptor);
  BoidPtr ptrBoid = m_actor->ptrToBoid;

  enVector2 const behavior = Boid::flee(*ptrBoid,
                                        ptrDesc->m_target->getPosition(),
                                        ptrDesc->m_magnitude,
                                        ptrDesc->m_radiusUtilSafe);

  if( ptrBoid->getDistanceTo(*ptrDesc->m_target) <= ptrDesc->m_radiusUtilSafe )
  {
    m_actor->boidState = stateFlags::idle;
  }

  ptrBoid->addForce(behavior);
  ptrBoid->update(elapsedTime);

  return  m_actor->boidState;
}
