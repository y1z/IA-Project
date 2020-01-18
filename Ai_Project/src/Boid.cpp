#include "Boid.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "..\include\Boid.h"

Boid::Boid()
  :m_position(enVector2::zeroVector),
  m_speed(100.0f),
  m_aceleration(1.0f),
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
    std::cerr << "failed to load sprite \n"<< "PATH = \'" <<pathToSprite << "\'\n";
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
  if (!(m_position == m_prevPosition)) {
    m_prevPosition = m_position;
  }
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
  return m_aceleration;
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
Boid::setAcceleration(float newAccelration)
{
  m_aceleration = newAccelration;
}

void
Boid::setMass(float newMass)
{
  m_mass = newMass;
}

enVector2
Boid::seek(const enVector2& myPos,
  const enVector2& TargetPos,
  float desiredMagnitude)
{
  enVector2 PathToTarget = TargetPos - myPos;
  PathToTarget.NormalizeSelf();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
}

enVector2
Boid::flee(const enVector2& myPos,
  const enVector2& TargetPos,
  float desiredMagnitude,
  float desiredDistance)
{
  if ((myPos - TargetPos).Magnitude() <= desiredDistance) {
    return  Boid::seek(myPos, TargetPos, desiredMagnitude) * -1.0f;
  }

  return enVector2(enVector2::zeroVector);
}

enVector2
Boid::pursue(const enVector2& myPos,
  const Boid& Target,
  float desiredMagnitude,
  float deltaTime)

{
  enVector2 newTargetPosition = Target.getDir() * Target.getSpeed() * deltaTime;

  return  Boid::seek(myPos, newTargetPosition, desiredMagnitude); //enVector2();
}

enVector2
Boid::evade(const enVector2& myPos,
  const Boid& Target,
  float desiredMagnitude,
  float deltaTime,
  float desiredDistance)
{
  enVector2 newTargetPosition = Target.getDir() * Target.getSpeed() * deltaTime;

  return Boid::flee(myPos, newTargetPosition, desiredMagnitude, desiredDistance);
}

enVector2
Boid::arrival(const enVector2& myPos,
  const enVector2& TargetPos,
  float desiredMagnitude,
  float radius)
{
  const float difference = (TargetPos - myPos).Magnitude();

  if (difference >= radius) {
    return Boid::seek(myPos, TargetPos, desiredMagnitude);
  }

  return Boid::seek(myPos, TargetPos, desiredMagnitude) * (difference / radius);
}

