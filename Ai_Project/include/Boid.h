#pragma once
#include "enVector2D.h"
#include "enNode.h"
#include "enCircularLinkList.h"
#include "cIndexer.h"

#include "SFML/Graphics.hpp"

  /**
  * @brief :Is a A,I agents position and movement.
  * @bug : no known bugs.
  */
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
  * @param[in] elapsedTime : used to know how much time has passed.
  * @bug : no known bugs
  */
  void
  update(float elapsedTime);

/**
* @brief : add force to the current vector
* @bugs : no known bugs
* @param[in] additionalForce : the force that added to the force vector
*/
  void
  addForce(const enVector2& additionalForce);

/**
* @brief : sets force of the boid
* @bugs : no known bugs
* @param[in] newForce: the new force of the vector
*/
  void
  setForce(const enVector2& newForce);

  /**
  *  @returns :the direction of the boid.
  */
  enVector2
  getDir()const;

  /**
  * @returns : the current force the boid uses to move.
  * @bug : no known bugs
  */
  enVector2
  getForce()const;

  /**
  * @returns : the previously used force for movement
  * @bug :no known bugs
  */
  enVector2
  getPrevForce()const;

  /**
  * @returns : the current position of the boid
  * @bug : no known bugs
  */
  enVector2
  getPosition() const;

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
  * @return : the distance between the boid position and a vector
  * @param[in] otherVector : the vector to get the distance to.
  * @bug : no known bugs
  */
  float 
  getDistanceTo(const enVector2& otherVector)const;

  /**
  * @return : the distance between the position of 2 boids.
  * @param[in] otherBoid : the boid to get the distance to.
  * @bug : no known bugs
  */
  float
  getDistanceTo(const Boid &otherBoid) const;

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
  setMaxForce(float newMaxForce);

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

  /**
  * @brief : used to set the boid in a wandering state 
  * @param[in] isWandering : used to set if the boid is wandering or not.
  * @bug : no known bugs
  */
  void
  setWander(bool isWandering);
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
  static enVector2
  wander(Boid& myBoid,
         float desiredMagnitude,
         float angle,
         float circleRadius,
         float PredictionTime,
         float minimumWanderTime = 1.0f,
         sf::RenderWindow* window = nullptr);

  /**
  * @returns : a vector directing the boid to the currently selected node. 
  * @bug :no known bugs.
  */
  static enVector2 
  followPath(Boid& myBoid,
             enCircularLinkList<enNode>& positions,
             float desiredMagnitude = 1.0f,
             sf::RenderWindow * window = nullptr);
  /**
  * @brief : the same as follow-path but when the last node is reached start going
  *          in reverse order.
  * @bug :no known bugs.
  */
  static enVector2 
  patrol(Boid& myBoid,
         enCircularLinkList<enNode>& positions,
         float desiredMagnitude = 1.0f,
         sf::RenderWindow* window = nullptr);
private:
  /**
  * @brief : limits how much force can be in 'm_forceSum'.
  * @bug : no known bugs.
  */
  void 
  LimitForceSum();
  

public:
  /**
  * @brief : the container of the sprite for the boid
  */

  sf::Sprite m_sprite;
  /**
  * @brief : this contains
  */

  sf::Texture m_texture;

  /**
  * @brief : this is the force that will affect the force sum
  */
  enVector2 m_force;

  /**
  * @brief : this controls the force that will be used to move the boid
  */
  enVector2 m_forceSum;

  /**
  * @brief : this is the previous force used by the vector
  */
  enVector2 m_prevForce;

  /**
  * @brief : this is where the Boid is located
  */
  enVector2 m_position;

  /**
  * @brief : this is the previous location of the boid
  */
  enVector2 m_prevPosition;

  /**
  * @brief : used to keep track of which node the boid is following if 
  *          any.
  * @bug : no known bugs
  */
  cIndexer m_nodeIndex;
private:


  /**
  * @brief : how fast the boid is 
  */
  float m_speed;

  /**
  * @brief : how much force can we give a boid
  */
  float m_maxForce;

  /**
  * @brief : how much the boid can increment its speed
  */
  float m_acceleration;

  /**
  * @brief : how difficult it is for the boid to turn
  */
  float m_mass;

  /**
  * @brief : to know how much more time to spend wandering.
  * @bug : no known bugs.
  */
  float m_currentWanderTime;

  

  /**
  * @brief : used to know if the boid is a wandering state.
  * @bug :
  */
  bool is_wandering = false;

  enum class ForceAplication
  {
    Normal = 0,
    Wander = 1
  };

  ForceAplication m_forceAplication = ForceAplication::Normal;
};

