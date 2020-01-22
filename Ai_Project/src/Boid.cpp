#include "Boid.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "..\include\Boid.h"

Boid::Boid()
  :m_position(enVector2::zeroVector),
  m_speed(100.0f),
  m_maxMagnitude(10.0f),
  m_acceleration(1.0f),
  m_mass(0.5f)
{
}

Boid::Boid(float x, float y)
  :Boid()
{
  m_position.X = x;
  m_position.Y = y;
}

bool
Boid::loadSprite(const std::string& pathToSprite)
{
  if (!m_texture.loadFromFile(pathToSprite))
  {
    std::cerr << "failed to load sprite \n" << "PATH = \'" << pathToSprite << "\'\n";
    return false;
  }
  else {
    m_sprite.setTexture(m_texture);
  }
  return true;
}

void
Boid::update()
{
  if (!(m_position == m_prevPosition))
  {
    m_prevPosition = m_position;
  }

  const float Mag = m_force.Magnitude();
  if (m_maxMagnitude < Mag)
  {
    const float reciproical = 1.0f / Mag;
    m_force *= reciproical * m_maxMagnitude;
  }

  enVector2 newPosition((m_position + m_force));
  
  m_position += (newPosition - m_position) * m_mass;

}

void
Boid::addForce(const enVector2& additionalForce)
{
  m_force += additionalForce;
}

enVector2
Boid::getDir() const
{
  return (m_position - m_prevPosition).NormalizeReturn();
}

float
Boid::getSpeed() const
{
  return  m_speed;
}

float
Boid::getAcceleration() const
{
  return m_acceleration;
}

float
Boid::getMass() const
{
  return m_mass;
}

void
Boid::setPosition(float x, float y)
{
  m_position.X = x;
  m_position.Y = y;
}

void
Boid::setSpeed(float newSpeed)
{
  m_speed = newSpeed;
}

void
Boid::setMaxMagnitude(float newMaxMagnitude)
{
  m_maxMagnitude = newMaxMagnitude;
}

void
Boid::setAcceleration(float newAcceleration)
{
  m_acceleration = newAcceleration;
}

void
Boid::setMass(float newMass)
{
  m_mass = newMass;
}

enVector2 Boid::seek(const Boid& myBoid,
  const Boid& Target,
  float desiredMagnitude)

{
  enVector2 PathToTarget = (Target.m_position - myBoid.m_position).NormalizeReturn() * myBoid.getMass();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
}

enVector2 Boid::seek(const Boid& myBoid,
  const enVector2& TargetPos,
  float desiredMagnitude)
{

  enVector2 PathToTarget = (TargetPos - myBoid.m_position).NormalizeReturn() * myBoid.getMass();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
}


enVector2
Boid::flee(const Boid& myBoid,
  const enVector2& TargetPos,
  float desiredMagnitude,
  float desiredDistance)
{
  if ((myBoid.m_position - TargetPos).Magnitude() <= desiredDistance) {
    return  Boid::seek(myBoid, TargetPos, desiredMagnitude) * -1.0f;
  }

  return enVector2(enVector2::zeroVector);
}

enVector2
Boid::pursue(const Boid& myBoid,
  const Boid& Target,
  float desiredMagnitude,
  float deltaTime)

{
  enVector2 newTargetPosition = Target.m_position + (Target.getDir() * Target.getSpeed() * deltaTime);

  if (Target.m_position.Distance(newTargetPosition) < myBoid.m_position.Distance(Target.m_position))
  {
    return Boid::seek(myBoid, Target.m_position, desiredMagnitude);
  }

  return Boid::seek(myBoid, newTargetPosition, desiredMagnitude);
}

enVector2
Boid::evade(const Boid& myBoid,
  const Boid& Target,
  float desiredMagnitude,
  float deltaTime,
  float desiredDistance)
{
  enVector2 newTargetPosition = Target.m_position + (Target.getDir() * Target.getSpeed() * deltaTime);

  return Boid::flee(myBoid, newTargetPosition, desiredMagnitude, desiredDistance);
}

enVector2
Boid::arrive(const Boid& myBoid,
  const enVector2& TargetPos,
  float desiredMagnitude,
  float radius)
{
  const float difference = (TargetPos - myBoid.m_position).Magnitude();

  if (difference >= radius) {
    return Boid::seek(myBoid, TargetPos, desiredMagnitude);
  }

  return Boid::seek(myBoid, TargetPos, desiredMagnitude) * (difference / radius);
}

