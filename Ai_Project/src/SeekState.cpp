#include "..\include\SeekState.h"


static seekStateArgs c_defaultArgs;

SeekState::SeekState()
{

 this->m_currentStateFlag = stateFlags::seek;

}

void
SeekState::onEnter()
{
  LOG_MSG(" entered seek state ");
  if( m_actor->ptrToStateDescriptor == nullptr )
  {
    m_actor->ptrToStateDescriptor = &c_defaultArgs;
  }
  m_actor->hasEntered = true;

}

void
SeekState::onExit()
{
  m_actor->hasEntered = false;
  m_actor->ptrToStateDescriptor = nullptr;
  LOG_MSG("exited seek state");
}

stateFlags
SeekState::update(float elapsedTime)
{
  seekStateArgs* ptrDescriptor = static_cast<seekStateArgs*> (m_actor->ptrToStateDescriptor);
  enVector2 const TargetPosition = ptrDescriptor->m_target->getPosition();

  enVector2 Behavior = Boid::seek(*m_actor->ptrToBoid,
                                  TargetPosition,
                                  ptrDescriptor->m_magnitude);

  if( m_actor->ptrToBoid->getDistanceTo(TargetPosition) < ptrDescriptor->m_radiusUtilStateChange )
  {
    m_actor->boidState = stateFlags::idle; 
  }

  m_actor->ptrToBoid->addForce(Behavior);
  m_actor->ptrToBoid->update(elapsedTime);
  const enVector2 position = m_actor->ptrToBoid->getPosition();
  m_actor->ptrToBoid->m_sprite.setPosition(position.X, position.Y);

  return m_actor->boidState;
}
