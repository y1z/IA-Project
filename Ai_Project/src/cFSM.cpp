#include "cFSM.h"
#include "SeekState.h"
#include "IdleState.h"
#include "FleeState.h"
#include "WanderState.h"
#include "helper.h"

#include <cstdint>


cFSM::cFSM()
{

  for( BaseState*& statePtr : m_StateContainer )
  {
    statePtr = nullptr;
  }

}

cFSM::~cFSM()
{

  for( BaseState*& statePtr : m_StateContainer )
  {
    if( statePtr != nullptr )
    {
      delete statePtr;
    }
  }

}


bool
cFSM::init(std::vector<Boid>& boidsContainer,
           Boid* ptrToTarget)
{
  if( !this->extractBoidData(boidsContainer) )
    return false;

  if( !this->initStates() )
    return false;

  if( !this->initArgsForStates(ptrToTarget) )
    return false;


  return true;
}


void
cFSM::executeMachine(float elapsedTime)
{

  for( sBoidPtrAndState& boid : m_boidsAndState )
  {
    m_StateContainer[(int)boid.boidState]->m_actor = &boid;
    if( !boid.hasEntered )
    {
      m_StateContainer[(int)boid.boidState]->onEnter();
    }
    else
    {
      stateFlags const flagRequiredForState = m_StateContainer[(int)boid.boidState]->m_currentStateFlag;
      stateFlags const currentState = m_StateContainer[(int)boid.boidState]->update(elapsedTime);

      if( flagRequiredForState != currentState )
      {
        m_StateContainer[(int)flagRequiredForState]->onExit();
      }

    }
    enVector2 const position = boid.ptrToBoid->getPosition();
    boid.ptrToBoid->m_sprite.setPosition(position.X, position.Y);
  }

  this->assignArgsForBehavior();
}

void
cFSM::assignArgsForBehavior()
{

  for( sBoidPtrAndState& boid : m_boidsAndState )
  {

    switch( boid.boidState )
    {
      case stateFlags::idle:
        boid.ptrToStateDescriptor = &m_idleStateArguments;
        break;
      case stateFlags::seek:
        boid.ptrToStateDescriptor = &m_seekArguments;
        break;
      case stateFlags::flee:
        boid.ptrToStateDescriptor = &m_fleeStateArguments;
        break;
      case stateFlags::wander:
      boid.ptrToStateDescriptor = &m_wanderStateArguments;
        break;
      default:
        break;
    }

  }


}


bool
cFSM::extractBoidData(std::vector<Boid>& boidsContainer)
{

  for( size_t i = 0u; i < boidsContainer.size() - 1; ++i )
  {
    m_boidsAndState.emplace_back(sBoidPtrAndState());
    m_boidsAndState[i].ptrToBoid = &boidsContainer[i];
    m_boidsAndState[i].boidState = stateFlags::seek;
    m_boidsAndState[i].ptrToStateDescriptor = &m_seekArguments;
  }
  return true;
}

bool
cFSM::initStates()
{
  try
  {
    m_StateContainer[(int)stateFlags::seek] = new SeekState();
    m_StateContainer[(int)stateFlags::idle] = new IdleState();
    m_StateContainer[(int)stateFlags::flee] = new FleeState();
    m_StateContainer[(int)stateFlags::wander] = new  WanderState();
  }
  catch( const std::exception & e )
  {
    std::cerr << e.what() << std::endl;
    return false;
  }

  return true;
}

bool 
cFSM::initArgsForStates(Boid* ptrToTarget)
{
  if( ptrToTarget != nullptr )
  {
    m_pTarget = ptrToTarget;
    m_seekArguments.m_target = m_pTarget;

    m_fleeStateArguments.m_target = m_pTarget;
    m_idleStateArguments.m_boids = &m_boidsAndState;
  }
  else { return false; }

  return true;
}
