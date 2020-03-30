#include "Boid.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "..\include\Boid.h"
#include "enCircularLinkList.h"
#include "helper.h"

#include <cstdint>
#include <random>


static uint32_t s_idCount = 0u;

Boid::Boid()
  :m_position(enVector2::zeroVector),
  m_prevForce(enVector2::northVector),
  m_speed(60.0f),
  m_maxForce(1.8f),
  m_acceleration(1.0f),
  m_mass(0.7f),
  m_wanderTimeTotal(0.0f),
  m_timeForWandering(0.0f),
  m_lastMomentumUpdate(0.0f),
  m_separationRadius(330.0f),
  m_momentumKeept(0.99f),
  m_minimumTimeForMomentiumLoss(1.0f/60.0f)
{
  m_id = ++s_idCount;
}

Boid::Boid(float x, float y)
  :Boid()
{
  m_position.X = x;
  m_position.Y = y;
}

Boid::Boid(enVector2 const& position)
  :Boid()
{
  m_position = position;
}

Boid::~Boid()
{
  --s_idCount;
}

bool
Boid::loadSprite(const std::string& pathToSprite)
{
  if( !m_texture.loadFromFile(pathToSprite) )
  {
    std::cerr << "failed to load sprite \n" << "PATH = \'" << pathToSprite << "\'\n";
    return false;
  }
  else
  {
    m_sprite.setTexture(m_texture);
  }
  return true;
}

void
Boid::update(float elapsedTime)
{

  if( !(m_position == m_prevPosition) )
  {
    m_prevPosition = m_position;
  }

  m_prevForce = m_forceSum;


  m_forceSum += m_force * m_mass * elapsedTime * m_speed;;
  m_position += m_forceSum;// m_forceSum; 

  this->LimitForceSum();
  this->updateMomentum(elapsedTime);
  m_sprite.setPosition(sfHelp::ConvertToSfmlVector(m_position));

  this->updateForceAplication(elapsedTime);
}

void 
Boid::updateForceAplication(float elapsedTime)
{
  if( is_Wandering == false )
  {
    m_force = enVector2::zeroVector;
  }
  else if( is_Wandering )
  {
    m_wanderTimeTotal += elapsedTime;
    if( m_wanderTimeTotal >= m_timeForWandering)
    {
      is_Wandering = false;
      m_wanderTimeTotal = 0.0f;
      m_timeForWandering = 0.0f;
      m_force = enVector2::zeroVector;
    }
  }
}

void 
Boid::updateMomentum(float elapsedTime)
{
  //float const Magnitude = (m_forceSum.Magnitude() > 0.0001f) ? m_forceSum.Magnitude() : 0.0001f;
  //enVector2 const momentumReduction = m_forceSum * (Magnitude * forceReduction);
  ////m_forceSum -= momentumReduction;
//  float const forceReduction = std::fabsf(1.0f - m_momentumKeept);

  m_forceSum *= m_momentumKeept * (1.0f - elapsedTime);

  m_lastMomentumUpdate += elapsedTime;
  if(m_minimumTimeForMomentiumLoss < m_lastMomentumUpdate )
  {
    float const Magnitude = (m_forceSum.Magnitude() > 0.0001f) ? m_forceSum.Magnitude() : 0.0001f;
// (m_forceSum * m_lastMomentumUpdate);  //  * (forceReduction * Magnitude * m_lastMomentumUpdate);
    m_lastMomentumUpdate = 0.00f;
  }
}

void
Boid::addForce(const enVector2& additionalForce)
{
  m_force += additionalForce;
}

void
Boid::setForce(const enVector2& newForce)
{
  m_force = newForce;
}

enVector2
Boid::getDir() const
{
  return (m_position - m_prevPosition).NormalizeReturn();
}

enVector2
Boid::getForce() const
{
  return m_force;
}

enVector2
Boid::getPrevForce() const
{
  return m_prevForce;
}

enVector2
Boid::getPosition() const
{
  return m_position;
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

uint32_t
Boid::getID() const
{
  return m_id;
}

float
Boid::getDistanceTo(const enVector2& otherVector) const
{
  return m_position.Distance(otherVector);
}


float
Boid::getDistanceTo(const Boid& otherBoid) const
{
  return this->m_position.Distance(otherBoid.m_position);
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
Boid::setMaxForce(float newMaxMagnitude)
{
  m_maxForce = newMaxMagnitude;
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

void 
Boid::setBoidWander(float timeToWander)
{
  m_forceAplication = ForceAplication::Wander;
  m_timeForWandering = timeToWander;
  is_Wandering = true;
}

enVector2
Boid::seek(const Boid& myBoid,
           const Boid& Target,
           float desiredMagnitude)

{
  enVector2 PathToTarget = (Target.m_position - myBoid.m_position).NormalizeReturn();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
}

enVector2
Boid::seek(const Boid& Target,
           float  strengthOfForce)
{
  enVector2 PathToTarget = (Target.m_position - this->m_position).NormalizeReturn();
  PathToTarget *= strengthOfForce;
  m_force += PathToTarget;
  return PathToTarget;
}

enVector2
Boid::seek(const enVector2& Target,
           float desiredMagnitude)
{
  enVector2 PathToTarget = (Target - this->m_position).NormalizeReturn();
  PathToTarget *= desiredMagnitude;
  m_force += PathToTarget;
  return PathToTarget;
}

enVector2
Boid::seek(const Boid& myBoid,
           const enVector2& TargetPos,
           float desiredMagnitude)
{

  enVector2 PathToTarget = (TargetPos - myBoid.m_position).NormalizeReturn();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
}

enVector2
Boid::seek(const enVector2& myPos,
           const enVector2& TargetPos,
           float desiredMagnitude)
{
  enVector2 PathToTarget = (TargetPos - myPos).NormalizeReturn();
  PathToTarget *= desiredMagnitude;
  return PathToTarget;
}


enVector2
Boid::flee(const Boid& myBoid,
           const enVector2& TargetPos,
           float desiredMagnitude,
           float desiredDistance)
{
  if( (myBoid.m_position - TargetPos).Magnitude() <= desiredDistance )
  {
    return  Boid::seek(myBoid, TargetPos, desiredMagnitude) * -1.0f;
  }

  return enVector2(enVector2::zeroVector);
}

enVector2
Boid::flee(const enVector2& TargetPos,
           float strengthOfForce,
           float desiredDistance)
{

  if( (this->m_position - TargetPos).Magnitude() <= desiredDistance )
  {
    enVector2 const fleeFroce = this->seek(TargetPos, strengthOfForce) * -1.0f;
    m_force += fleeFroce;
    return  fleeFroce;
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

  if( Target.m_position.Distance(newTargetPosition) > myBoid.m_position.Distance(Target.m_position) )
  {
    return Boid::seek(myBoid, Target.m_position, desiredMagnitude);
  }

  return Boid::seek(myBoid, newTargetPosition, desiredMagnitude);
}

enVector2
Boid::pursue(const Boid& Target,
             float strengthOfForce,
             float deltaTime)
{
  enVector2 const newTargetPosition = Target.m_position + (Target.getDir() * Target.getSpeed() * deltaTime);

  if( Target.getDistanceTo(newTargetPosition) > this->getDistanceTo(Target.m_position) )
  {
    enVector2 const result = this->seek(Target, strengthOfForce);
    m_force += result;
    return result;
  }

  enVector2 const result = this->seek(newTargetPosition, strengthOfForce);
  m_force += result;
  return result;
}

enVector2
Boid::evade(const Boid& myBoid,
            const Boid& Target,
            float desiredMagnitude,
            float deltaTime,
            float desiredDistance)
{
  enVector2 newTargetPosition = Target.m_position + (Target.getDir() * Target.getSpeed() * deltaTime);

 // enVector2  newParallelVector = Target.m_position + (Target.getDir().ReturnFakeParallelVector() * Target.getSpeed() * deltaTime);

  //checking if boid is in the radius of the other boid
  if( Target.m_position.Distance(newTargetPosition) > myBoid.m_position.Distance(Target.m_position) )
  {
    return Boid::flee(myBoid,
                      Target.m_position,
                      desiredMagnitude,
                      desiredDistance);
  }

  return Boid::flee(myBoid, newTargetPosition, desiredMagnitude, desiredDistance);
}


enVector2
Boid::evade(const Boid& Target,
            float strengthOfForce,
            float deltaTime,
            float desiredDistance)
{
  enVector2 const newTargetPosition = Target.m_position + (Target.getDir() * Target.getSpeed() * deltaTime);

 // enVector2  newParallelVector = Target.m_position + (Target.getDir().ReturnFakeParallelVector() * Target.getSpeed() * deltaTime);

  if( Target.getDistanceTo(newTargetPosition) > this->getDistanceTo(Target.m_position) )
  {
    enVector2 const resultingVector = this->flee(Target.getPosition(), strengthOfForce, desiredDistance);
    m_force += resultingVector;
    return  resultingVector;
  }
  enVector2 const resultingVector = this->flee(newTargetPosition, strengthOfForce, desiredDistance);
  m_force += resultingVector;
  return  resultingVector;
}

enVector2
Boid::arrive(const Boid& myBoid,
             const enVector2& TargetPos,
             float desiredMagnitude,
             float radius)
{
  const float difference = (TargetPos - myBoid.m_position).Magnitude();

  if( difference >= radius )
  {
    return Boid::seek(myBoid, TargetPos, desiredMagnitude);
  }

  return Boid::seek(myBoid, TargetPos, desiredMagnitude) * (difference / radius);
}


enVector2
Boid::arrive(const enVector2& TargetPos,
             float strengthOfForce,
             float radius)
{
  const float differenceSquared = (TargetPos - m_position).SquaredMagnitude();
  const float radiusSquared = (radius * radius);

  if( differenceSquared >= radiusSquared )
  {
    enVector2 const result = this->seek(TargetPos, strengthOfForce);
    m_force += result;
    return result;
  }
  enVector2 const result = this->seek(TargetPos, strengthOfForce) * (differenceSquared / radiusSquared);
  m_force += result;
  return result;
}


enVector2
Boid::wanderBehavior(float strengthOfForce,
                     float inputAngle,
                     float circleRadius,
                     float PredictionTime,
                     float minimumWanderTime)
{

  if( this->is_Wandering == false )
  {
    // find out what direction I'm going in
    enVector2 currentDirection = this->getDir();
    // find out where i am going  
    enVector2 const FuturePosition =
      this->getPosition() + (currentDirection * strengthOfForce * getSpeed() * PredictionTime);

    const float percentageChange = sfHelp::RandFloatRange(0.0f, 1.0f);
    const float ChangeInAngle = (percentageChange * inputAngle) - (inputAngle * .5f);

    currentDirection *= circleRadius;
    currentDirection.RotateSelfRad(ChangeInAngle);

    enVector2 const FinalPosition = (FuturePosition) + (currentDirection);

    m_wanderTimeTotal = 0.00f;
    this->setBoidWander(minimumWanderTime);

    enVector2 const result = this->seek(FinalPosition, strengthOfForce);
    m_force += result;
    return result; 
  }

  return enVector2::zeroVector;
}


enVector2
Boid::followPath(enCircularLinkList<enPathNode>& nodes,
                 float strengthOfForce,
                 sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = m_nodeIndex.getIndex();
  enPathNode* ptrToNode = nodes.getPtr(currentIndex);

  if( getDistanceTo(ptrToNode->m_position) < ptrToNode->m_radius )
  {
    m_nodeIndex.incrementIndex();
    m_nodeIndex.resetIfIndexEqualsMax(nodes.getSize());
    currentIndex = m_nodeIndex.getIndex();
  }

  if( currentIndex == 0 )
  {
    result = this->seek(ptrToNode->m_position, strengthOfForce);
  }
  else
  {
    enPathNode* ptrToPreviousNode = nodes.getPtr(currentIndex - 1);

    const enVector2 directPathToNode = ptrToNode->m_position - getPosition();

    const enVector2 pathBetweenNodes = enVector2(ptrToNode->m_position - ptrToPreviousNode->m_position);

    const enVector2 pathFromPreviousNodeToBoid = (getPosition() - ptrToPreviousNode->m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);

    const enVector2 finalPath = (correctionVector + directPathToNode);

    if( window != nullptr )
    {
      sf::VertexArray const Line = sfHelp::CreateVisualLine(getPosition(),
                                                            finalPath,
                                                            1.0f);

      window->draw(Line);
    }

    result = this->seek(finalPath + getPosition(), strengthOfForce);
  }

  m_force += result;

  return result;
}


enVector2
Boid::followPath(std::vector<enPathNode>& nodes,
                 float desiredMagnitude,
                 sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = m_nodeIndex.getIndex();
  enPathNode currentNode = nodes.at(currentIndex);

  if( getDistanceTo(currentNode.m_position) < currentNode.m_radius )
  {
    m_nodeIndex.incrementIndex();
    m_nodeIndex.resetIfIndexEqualsMax(nodes.size());
    currentIndex = m_nodeIndex.getIndex();
  }

  if( currentIndex == 0 )
  {
    result = this->seek(currentNode.m_position, desiredMagnitude);
  }
  else
  {
    enPathNode ptrToPreviousNode = nodes.at(currentIndex - 1);

    const enVector2 directPathToNode = currentNode.m_position - getPosition();

    const enVector2 pathBetweenNodes = enVector2(currentNode.m_position - ptrToPreviousNode.m_position);

    const enVector2 pathFromPreviousNodeToBoid = (getPosition() - ptrToPreviousNode.m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);


    enVector2 const finalPath = (correctionVector + directPathToNode);// + getPosition();

    if( window != nullptr )
    {
      sf::VertexArray Line = sfHelp::CreateVisualLine(getPosition(),
                                                      finalPath,
                                                      1.0f);

      window->draw(Line);
    }

    result = this->seek(finalPath + getPosition(), desiredMagnitude);
  }

  m_force += result;

  return result;
}

enVector2 
Boid::patrol(enCircularLinkList<enPathNode>& nodes,
             float desiredMagnitude,
             sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = m_nodeIndex.getIndex();
  enPathNode* ptrToNode = nodes.getPtr(currentIndex);


  if( getDistanceTo(ptrToNode->m_position) < ptrToNode->m_radius )
  {

    if( currentIndex == 0 )
    {
      m_nodeIndex.setIncrementAmount(1);
    }
    else if( currentIndex == nodes.getSize() - 1 )
    {
      m_nodeIndex.setIncrementAmount(-1);
    }

    m_nodeIndex.incrementByIncrementAmount();
    currentIndex = m_nodeIndex.getIndex();
  }

  if( currentIndex == 0 )
  {
    result = this->seek(ptrToNode->m_position, desiredMagnitude);
  }
  else
  {
    enPathNode* ptrToPreviousNode = nodes.getPtr(currentIndex - 1);

    const enVector2 directPathToNode = ptrToNode->m_position - getPosition();

    const enVector2 pathBetweenNodes = enVector2(ptrToNode->m_position - ptrToPreviousNode->m_position);

    const enVector2 pathFromPreviousNodeToBoid = (getPosition() - ptrToPreviousNode->m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);

    enVector2 const finalPath = (correctionVector + directPathToNode);// + getPosition();

    if( window != nullptr )
    {
      sf::VertexArray Line = sfHelp::CreateVisualLine(getPosition(),
                                                      finalPath,
                                                      1.0f);


      window->draw(Line);
    }

    result = this->seek(finalPath + getPosition(), desiredMagnitude);
  }

  m_force += result;
  return result;
}

enVector2
Boid::patrol(std::vector<enPathNode>& nodes,
             float desiredMagnitude,
             sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = m_nodeIndex.getIndex();
  enPathNode currentNode = nodes.at(currentIndex);

  if( getDistanceTo(currentNode.m_position) < currentNode.m_radius )
  {

    if( currentIndex == 0 )
    {
      m_nodeIndex.setIncrementAmount(1);
    }
    else if( currentIndex == nodes.size() - 1 )
    {
      m_nodeIndex.setIncrementAmount(-1);
    }

    m_nodeIndex.incrementByIncrementAmount();
    currentIndex = m_nodeIndex.getIndex();
  }

  if( currentIndex == 0 )
  {
    result = this->seek(currentNode.m_position, desiredMagnitude);
  }
  else
  {
    enPathNode PreviousNode = nodes.at(currentIndex - 1);

    const enVector2 directPathToNode = currentNode.m_position - getPosition();

    const enVector2 pathBetweenNodes = enVector2(currentNode.m_position - PreviousNode.m_position);

    const enVector2 pathFromPreviousNodeToBoid = (getPosition() - PreviousNode.m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);

    enVector2 const finalPath = (correctionVector + directPathToNode);// + getPosition();

    if( window != nullptr )
    {
      sf::VertexArray Line = sfHelp::CreateVisualLine(getPosition(),
                                                      finalPath,
                                                      1.0f);


      window->draw(Line);
    }

    result = this->seek(finalPath + getPosition(), desiredMagnitude);
  }
  m_force += result;
  return result;
}


enVector2
Boid::Separation(std::vector<Boid>& BoidsInTheGroup,
                 float desiredMagnitude)
{
  enVector2 result(enVector2::zeroVector);
  for( Boid& boidInGroup : BoidsInTheGroup )
  {
    float const distance = boidInGroup.getDistanceTo(this->getPosition());
    float const radius = boidInGroup.m_separationRadius;
    if( distance < radius )
    {
      result += boidInGroup.getDir() * (1 - ((distance + 0.000001f) / radius)) * desiredMagnitude;
    }
  }

  return result;
}

enVector2 
Boid::Cohesion(std::vector<Boid>& BoidsInTheGroup,
               float desiredMagnitude)
{
  enVector2 result(enVector2::zeroVector);

  for( Boid& boidInGroup : BoidsInTheGroup )
  {
    result += boidInGroup.getPosition();
  }

  float const reciprocalOfSize = 1.0f / static_cast<float>(BoidsInTheGroup.size());

  result *= reciprocalOfSize;
  return this->seek(result, desiredMagnitude);
}


enVector2
Boid::Cohesion(Boid& currentPosition,
               std::vector<Boid>& BoidsInTheGroup,
               float desiredMagnitude)
{
  enVector2 result(enVector2::zeroVector);

  for( Boid& boidInGroup : BoidsInTheGroup )
  {
    result += boidInGroup.getPosition();
  }

  float const reciprocalOfSize = 1.0f / static_cast<float>(BoidsInTheGroup.size());

  result *= reciprocalOfSize;

  return Boid::seek(currentPosition, result, desiredMagnitude);
}

enVector2
Boid::GroupDirection(std::vector<Boid>& BoidsInTheGroup,
                     float desiredMagnitude)
{
  enVector2 result(enVector2::zeroVector);

  for( Boid& boid : BoidsInTheGroup )
  {
    result += boid.getDir();
  }

  float const reciprocalOfSize = 1.0f / static_cast<float>(BoidsInTheGroup.size());

  result *= reciprocalOfSize * desiredMagnitude;
  return result;
}

enVector2
Boid::flocking(std::vector<Boid>& BoidsInTheGroup,
               float seperationMagnitude,
               float cohesionMagnitude,
               float directionMagnitude)
{
  enVector2 const result = this->Separation(BoidsInTheGroup, seperationMagnitude) +
    this->Cohesion(BoidsInTheGroup, cohesionMagnitude) +
    this->GroupDirection(BoidsInTheGroup, directionMagnitude);
  m_force += result;
  return result;
}


void
Boid::LimitForceSum()
{
  if( m_forceSum.SquaredMagnitude() >= (m_maxForce * m_maxForce) )
  {
    m_forceSum = m_forceSum.NormalizeReturn() * (m_maxForce);
  }

}

