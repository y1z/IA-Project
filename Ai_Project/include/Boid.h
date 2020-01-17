#pragma once
#include "CVector2D.h"
#include "SFML/Graphics.hpp"
#include <string>

class Boid
{
public:
  Boid();
  ~Boid() = default;

public:
  void
    loadSprite(const std::string& pathToSprite);

  /**
  *  @returns : the current value that represent the speed 
  */
  float 
    getSpeed() const;

  /**
  *  @returns : the current value that represent the acceleration
  */
  float
    getAcceleration()const;

  /**
  *  @returns : the current value that represent the mass
  */
  float
    getMass()const;

  void
    setPosition(float x, float y);

  void
    setSpeed(float newSpeed);

  void
    setAcceleration(float newAccelration);

  void
    setMass(float newMass);
public:

  static enVector2 seek(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude);

  static enVector2 flee(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude,
    float desiredDistance = 100.0f);


  static enVector2 pursue(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude,
    float desiredDistance = 100.0f,
    float predictionTime = 0.10f);


  static enVector2 evade(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude,
    float desiredDistance = 100.0f,
    float predictionTime = 0.10f);


  //TODO
  static enVector2 wander(const enVector2& myPos,
    float time);

  //TODO
  static enVector2 arrival(const enVector2& myPos,
    const enVector2& TargetPos,
    float maxMagnitude);

  //TODO: create nodes to follow .
  static enVector2 followPath(const enVector2& myPos,
    const enVector2& TargetPos,
    float maxMagnitude);

  sf::Sprite m_sprite;
  sf::Texture m_texture;
  enVector2 m_position;
private:

  float m_speed;
  float m_aceleration;
  float m_mass;
};

