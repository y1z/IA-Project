#pragma once
#include "enVector2.h"

#include "enPathNode.h"
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
  explicit Boid(enVector2 const& position);
  ~Boid();

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
  * @brief : updates how a force is applied
  * @bug :no known bugs.
  */
  void 
  updateForceAplication(float elapsedTime);

  /**
  * @brief : update how momentum affects the boid.
  * @bug :no known bugs.
  */
  void
  updateMomentum(float elapsedTime);

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
  * @returns : the boid id.
  */
  uint32_t
  getID() const;

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
  * @param[in] timeToWander: how long will the boid wander.
  * @bug : no known bugs
  */
  void
  setBoidWander(float timeToWander);
public:

  /**
  * @returns : a vector that gos directly to some target. 
  * @param[in] myPos : where the seeking boid is located.
  */
  static enVector2
  seek(const Boid& myPos,
       const Boid& TargetPos,
       float desiredMagnitude);

  /**
  * @returns a vector that gos directly to some target.
  * @param[in] TargetPos : where the target is located.
  * @param[in] strengthOfForce: the how strong the return vector is.
  * @bug : no known bugs
  */
  enVector2
  seek(const Boid& TargetPos,
       float strengthOfForce);


  /**
  * @param[in] TargetPos : where the target is located.
  * @param[in] strengthOfForce: the how strong the return vector is.
  * @bug : no known bugs
  */
  enVector2
  seek(const enVector2& TargetPos,
       float strengthOfForce);

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
  * @returns : a vector that gos directly to some target. 
  * @param[in] myPos : where the seeking boid is located.
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @bug : no known bugs
  */
  static enVector2 
  seek(const enVector2& myPos,
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
  * @returns : a vector that gos alway from some target (when the target is close enough). 
  * @param[in] TargetPos : where the target is located.
  * @param[in] desiredMagnitude : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs
  */
  enVector2
  flee(const enVector2& TargetPos,
       float strengthOfForce,
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
  * @returns : a vector that try to move to where the target is going to be.
  * @param[in] Target : where the target is located.
  * @param[in] strengthOfForce : the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs.
  */
  enVector2
  pursue(const Boid& Target,
         float strengthOfForce,
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
  * @param[in] Target : where the target is located.
  * @param[in] strengthOfForce: the how strong the return vector is.
  * @param[in] desiredDistance : how close the target to start fleeing.
  * @bug : no known bugs.
  */
  enVector2
  evade(const Boid& Target,
        float strengthOfForce,
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

  /**
  * @returns : a vector that will get close to some target then slow down.
  * @param[in] TargetPos : where the target is located.
  * @param[in] strengthOfForce : the how strong the return vector is.
  * @param[in] radius : how close the target needs to be, before we flee.
  * @bug : no known bugs.
  */
  enVector2 
  arrive(const enVector2& TargetPos,
         float strengthOfForce,
         float radius = 100.0f);

  /**
  * @brief : choses a location for the boid go towards and keep going to that location.
  * @param[in] strengthOfForce: how strong the resulting force.
  */
  enVector2
  wanderBehavior(float strengthOfForce,
                 float angle,
                 float circleRadius,
                 float PredictionTime,
                 float minimumWanderTime = 1.0f);

  /**
  * @brief : creates a path for the boid to follow.
  * @bug : no known bugs.
  */
  enVector2 
  followPath(enCircularLinkList<enPathNode>& positions,
             float strengthOfForce = 1.0f,
             sf::RenderWindow* window = nullptr);

  /**
  * @returns : a vector directing the boid to the currently selected node. 
  * @bug :no known bugs.
  */
  enVector2 
  followPath(std::vector<enPathNode>& positions,
             float desiredMagnitude = 1.0f,
             sf::RenderWindow* window = nullptr);

  /**
  * @brief : the same as follow-path but when the last node is reached start going
  *          in reverse order.
  * @bug :no known bugs.
  */
  enVector2 
  patrol(enCircularLinkList<enPathNode>& positions,
         float desiredMagnitude = 1.0f,
         sf::RenderWindow* window = nullptr);

  /**
  * @brief : the same as follow-path but when the last node is reached start going
  *          in reverse order.
  * @bug :no known bugs.
  */
  enVector2 
  patrol(std::vector<enPathNode>& positions,
         float desiredMagnitude = 1.0f,
         sf::RenderWindow* window = nullptr);

 /**
  * @returns : a vector that makes the boid keep it'stateFlags distance from every other boid.
  * @bug :no known bugs.
  */
  enVector2
  Separation(std::vector<Boid>& BoidsInTheGroup,
             float desiredMagnitude = 1.0f);

  /**
  * @returns : a vector that keep the group that the boid are a part of together.
  * @bug : no known bugs.
  */
  enVector2 
  Cohesion(std::vector<Boid>& BoidsInTheGroup,
           float desiredMagnitude = 1.0f);

  /**
  * @returns : a vector that keep the group that the boid are a part of together.
  * @bug : no known bugs.
  */
  static enVector2 
  Cohesion(Boid &currentPosition,
           std::vector<Boid>& BoidsInTheGroup,
           float desiredMagnitude = 1.0f);


  /**
  * @returns : the average direction of all the boid in the group.
  * @bug : no known bugs.
  */
  enVector2
  GroupDirection(std::vector<Boid>& BoidsInTheGroup,
                 float desiredMagnitude = 1.0f);

  /**
  * @returns : the sum of the following forces 'GroupDirection',
  *            'Cohesion' and 'Separation'. 
  * @bug : no known bugs.
  */
  enVector2
  flocking(std::vector<Boid>& BoidsInTheGroup,
           float seperationMagnitude,
           float cohesionMagnitude,
           float directionMagnitude);

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
  * @brief : this contains the underling image for each boid.
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
 
public:

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
  * @brief : control how much momentum the boid keep every time it slows down.
  */  
  float m_momentumKeept;

  /**
  * @brief : determines how much for does a boid needs before the momentum loss
  * kick in.
  */
  float m_minimumTimeForMomentiumLoss;

  /**
  * @brief : how difficult it is for the boid to turn
  */
  float m_mass;

  /**
  * @brief : to keep track of the amount of time spent wandering.
  */
  float m_wanderTimeTotal;

  /**
  * @brief : controls the amount of time the boid will wander.
  */
  float m_timeForWandering;

  /**
  * @brief : keeps track of how much time has passed seans the last time the boid has slowed down 
  */
  float m_lastMomentumUpdate;

  /**
  * @brief : the radius for the boid in the flocking behavior.
  */
  float m_separationRadius;

private:
  /**
  * @brief : give each boid a unique id.
  */
  uint32_t m_id; 

public:

  /**
  * @brief : controls how the force is applied each frame.
  */
  enum class ForceAplication
  {
    Normal = 0,
    Wander = 1
  };

  bool is_Wandering = false;

  ForceAplication m_forceAplication = ForceAplication::Normal;
};


using BoidPtr = Boid*;
using BoidRef = Boid&;

