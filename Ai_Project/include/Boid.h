#pragma once
#include "CVector2D.h"
#include "SFML/Graphics.hpp"
#include <string>

class Boid
{
public:
  Boid();
  Boid(float x, float y);
  ~Boid() = default;

public:
  void
    loadSprite(const std::string& pathToSprite);

  void
    update();

  /**
  *  @returns :the direction of the boid.
  */
  enVector2
    getDir()const;

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
/**
* @brief : set the position of the boid
*/
  void
    setPosition(float x, float y);

/**
* @brief : changes the speed of the boid
* @param newSpeed [in] : the new speed for the boid
*/
  void
    setSpeed(float newSpeed);

/**
* @brief : changes the speed of the boid
* @param newSpeed [in] : the new speed for the boid
*/
  void
    setAcceleration(float newAccelration);

/**
* @brief : changes the mass of the boid
* @param newSpeed [in] : the new mass for the boid
*/
  void
    setMass(float newMass);
public:

/**
* @brief : changes the mass of the boid
* @param newSpeed [in] : the new mass for the boid
*/
  static enVector2 seek(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude);

/**
* @brief : changes the mass of the boid
* @param newSpeed [in] : the new mass for the boid
*/

  static enVector2 flee(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude,
    float desiredDistance = 100.0f);


  static enVector2 pursue(const enVector2& myPos,
    const Boid& Target,
    float desiredMagnitude,
    float deltaTime);


  static enVector2 evade(const enVector2& myPos,
    const Boid& Target,
    float desiredMagnitude,
    float deltaTime,
    float desiredDistance = 100.0f);
    


  //TODO
  static enVector2 wander(const enVector2& myPos,
    float time);

  //TODO
  static enVector2 arrival(const enVector2& myPos,
    const enVector2& TargetPos,
    float desiredMagnitude,
    float radius = 100.0f);

  //TODO: create nodes to follow .
  static enVector2 followPath(const enVector2& myPos,
    const enVector2& TargetPos,
    float maxMagnitude);

  sf::Sprite m_sprite;
  sf::Texture m_texture;
  enVector2 m_position;
  enVector2 m_prevPosition;
private:

  float m_speed;
  float m_aceleration;
  float m_mass;
};

