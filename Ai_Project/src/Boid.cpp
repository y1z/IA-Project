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

void
Boid::loadSprite(const std::string& pathToSprite)
{
  if (!m_texture.loadFromFile(pathToSprite))
  {
    std::cerr << "failed to load sprite \n";

  }
  else {
    m_sprite.setTexture(m_texture);
  }

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
