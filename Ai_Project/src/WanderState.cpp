#include "..\include\WanderState.h"

WanderState::WanderState()
{
  m_currentStateFlag = stateFlags::wander;
}

void
WanderState::onEnter()
{
  LOG_MSG(" entered wander state");
  m_actor->hasEntered = true;
}

void
WanderState::onExit()
{
  LOG_MSG(" exited wander state");
  m_actor->hasEntered = false;
  m_actor->ptrToStateDescriptor = nullptr;
  this->removeForceByID(m_actor->ptrToBoid->getID());
}

stateFlags
WanderState::update(float elapsedTime)
{
  BoidPtr boid = m_actor->ptrToBoid;
  wanderStateArgs* descriptor = static_cast<wanderStateArgs*>(m_actor->ptrToStateDescriptor);
  enVector2 force(enVector2::zeroVector);

  bool const AlreadyExist = this->checkForID(boid);

  if( boid->m_wanderTimeTotal <= 0.0f && !AlreadyExist )
  {
    force = boid->wanderBehavior(descriptor->m_magnitude,
                                 descriptor->m_angle,
                                 descriptor->m_circleRadius,
                                 descriptor->m_perditionTime,
                                 descriptor->m_wanderingTime);

    addForceAndID(force, boid->getID());

    boid->addForce(force);
  }
  else
  {
    force = findForceByID(boid->getID());
    boid->addForce(force);
    if(boid->m_wanderTimeTotal <= 0.000001f )
    {
      m_actor->boidState = stateFlags::idle;
    }
  }

  boid->m_wanderTimeTotal -= elapsedTime;
  boid->update(elapsedTime);
  return  m_actor->boidState;
}

bool
WanderState::checkForID(BoidPtr boid)
{
  auto checkForKey = [boid](VectorAndID& possibleMatch )
  {
    return possibleMatch.ID == boid->getID();
  };


  auto isInContainer = std::find_if(m_idsAndForces.begin(),
                                    m_idsAndForces.end(),
                                    checkForKey);

  if( isInContainer != m_idsAndForces.end() )
    return true;

  return false;
}

void
WanderState::addForceAndID(enVector2& force, uint32_t newID)
{
  m_idsAndForces.push_back(VectorAndID(newID, force));
}

enVector2
WanderState::findForceByID(uint32_t newID) const
{
  auto const findTheID = [newID](const VectorAndID& possibleMatch) 
  {
    return possibleMatch.ID == newID;
  };

  auto result = std::find_if(m_idsAndForces.begin(),
                             m_idsAndForces.end(),
                             findTheID);

  if( result != m_idsAndForces.end() )
  {
    return result->force;
  }
  else
  {
    LOG_MSG("did not find boid id in 'wander state '");
    return enVector2::zeroVector;
  }

}

void
WanderState::removeForceByID(uint32_t newID)
{
  auto findTheID = [newID](VectorAndID& possibleMatch) {
    return possibleMatch.ID == newID;
  };

  auto removeThisBoid = std::find_if(m_idsAndForces.begin(),
                                     m_idsAndForces.end(),
                                     findTheID);

  m_idsAndForces.erase(removeThisBoid);

}


