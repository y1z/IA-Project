#pragma once
#include "enVector2D.h"
#include "SFML/Graphics.hpp"
#include <string>

class Boid
{
public:
  Boid();
  Boid(float x, float y);
  ~Boid() = default;

public:

  /**
  * @brief : loads a sprite from a file path
  * @param[in] : pathToSprite  this is the file that contains the sprite
  * @bugs : no known bugs
  */
  bool
  loadSprite(const std::string& pathToSprite);

  /**
  * @brief : moves the boid and tracks
  * @bug : no known bugs
  */
  void
  update();

/**
* @brief : add force to the current vector
* @bugs : no known bugs
* @param[in] force : the force that added to the force vector
*/
  void
  addForce(const enVector2& additionalForce);

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
  * @brief : sets the new limit for the force vector
  * @bugs : no known bugs
  */
  void
  setMaxMagnitude(float newMaxMagnitude);

  /**
  * @brief : changes the speed of the boid
  * @param newAcceleration[in] : the new Acceleration for the boid
  */
  void
  setAcceleration(float newAcceleration);

  /**
  * @brief : changes the mass of the boid
  * @param newMass [in] : the new mass for the boid
  */
  void
  setMass(float newMass);
public:

  /**
  * @returns : a vector that gos directly to some target. 
  * @param[in] myPos : where the seeking boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @bug : no known bugs
  */
  static enVector2
  seek(const Boid& myPos,
       const Boid& TargetPos,
       float desiredMagnitude);

  /**
  * @returns : a vector that gos directly to some target. 
  * @param[in] myPos : where the seeking boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @bug : no known bugs
  */
  static enVector2 
  seek(const Boid& myPos,
       const enVector2& TargetPos,
       float desiredMagnitude);


  /**
  * @returns : a vector that gos alway from some target (when the target is close enough). 
  * @param[in] myPos : where the fleeing boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs
  */
  static enVector2
  flee(const Boid& myBoid,
       const enVector2& TargetPos,
       float desiredMagnitude,
       float desiredDistance = 100.0f);

  /**
  * @returns : a vector that try to move to where the target is going to be.
  * @param[in] myPos : where the pursuing boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs.
  */
  static enVector2
  pursue(const Boid& myPos,
         const Boid& Target,
         float desiredMagnitude,
         float deltaTime);

  /**
  * @returns : a vector that will get close to some target then slow down.
  * @param[in] myPos : where the evading boid is located.
  * @param[in] Target : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs.
  */
  static enVector2
  evade(const Boid& myPos,
        const Boid& Target,
        float desiredMagnitude,
        float deltaTime,
        float desiredDistance = 100.0f);

  /**
  * @returns : a vector that will get close to some target then slow down.
  * @param[in] myPos : where the seeking boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs.
  */
  static enVector2 
  arrive(const Boid& myBoid,//arrive
         const enVector2& TargetPos,
         float desiredMagnitude,
         float radius = 100.0f);


  //TODO : implement
  static enVector2 wander(const enVector2& myPos,
                          float time);

  //TODO: create nodes to follow .
  static enVector2 followPath(const enVector2& myPos,
                              const enVector2& TargetPos,
                              float maxMagnitude);
  /**
  * @brief :
  */

  sf::Sprite m_sprite;
  /**
  * @brief : this contains
  */

  sf::Texture m_texture;

  /**
  * @brief :this is the current force that affects the Boid
  */
  enVector2 m_force;

  /**
  * @brief : this is where the Boid is located
  */
  enVector2 m_position;

  /**
  * @brief : this is the previous location of the boid
  */
  enVector2 m_prevPosition;

private:
  /**
  * @brief : how fast the boid is 
  */
  float m_speed;

  /**
  * @brief : how fast the boid can get.
  */
  float m_maxSpeed;

  /**
  * @brief : how much the boid can increment its speed
  */
  float m_acceleration;

  /**
  * @brief : how difficult it is for the boid to turn
  */
  float m_mass;
};

