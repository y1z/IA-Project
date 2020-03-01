#include "Boid.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "..\include\Boid.h"
#include "enCircularLinkList.h"
#include "helper.h"

#include <cstdint>
#include <random>

Boid::Boid()
  :m_position(enVector2::zeroVector),
  m_speed(5.0f),
  m_maxForce(50.0f),
  m_acceleration(1.0f),
  m_mass(0.7f),
  m_currentWanderTime(0.0f)
{}

Boid::Boid(float x, float y)
  :Boid()
{
  m_position.X = x;
  m_position.Y = y;
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
  m_forceSum += m_force * m_mass * elapsedTime;
  m_position += m_forceSum * m_speed;
  this->LimitForceSum();
  m_forceSum *= 0.99f;

  if( m_forceAplication == ForceAplication::Normal )
  {
    m_force = enVector2::zeroVector;
  }

  else if( m_forceAplication == ForceAplication::Wander )
  {
    m_currentWanderTime -= elapsedTime;
    if( m_currentWanderTime < 0.0f )
    {
      m_forceAplication = ForceAplication::Normal;
      m_currentWanderTime = 0.0f;
      m_force = enVector2::zeroVector;
    }
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
Boid::setWander(bool isWandering)
{
  if( isWandering )
  {
    m_forceAplication = ForceAplication::Wander;
  }
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
Boid::seek(const Boid& myBoid,
           const enVector2& TargetPos,
           float desiredMagnitude)
{

  enVector2 PathToTarget = (TargetPos - myBoid.m_position).NormalizeReturn();
  PathToTarget *= desiredMagnitude;
  return  PathToTarget;
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
Boid::wander(Boid& myBoid,
             float desiredMagnitude,
             float angle,
             float circleRadius,
             float PredictionTime,
             float minimumWanderTime,
             sf::RenderWindow* window)
{
  static std::default_random_engine RandomNumber(std::time(nullptr));
  const std::uniform_real_distribution<float> Limits(0.0, 1.0);

  // find out what direction I'm going in
  enVector2 currentDirection = myBoid.getDir();
  // find out where i am going  
  enVector2 FuturePosition = myBoid.getPosition() + (currentDirection * desiredMagnitude * myBoid.getSpeed()) * PredictionTime;

  if( window )
  {
    sf::CircleShape circule(circleRadius);
    circule.setOrigin(circleRadius, circleRadius);
    circule.move(sfHelp::ConvertToSfmlVector(FuturePosition));
    circule.setFillColor(sf::Color::Blue);
    window->draw(circule);
  }
  if( myBoid.m_currentWanderTime <= 0.00f )
  {

    const float angleForBoid = currentDirection.getAngle();
    const float percentageChange = Limits(RandomNumber);
    const float ChangeInAngle = ((percentageChange * angle) - (angle * .5f)) + angleForBoid;
    std::cout << "angle of the boid = " << angleForBoid << '\n';
    std::cout << "percentage change in angle = " << percentageChange << '\n';
    std::cout << " ChangeInAngle = " << ChangeInAngle << '\n';

    //float ChangeInAngle = currentDirection.getAngle() +
    //  (Limits(RandomNumber) * angle) -
    //  (angle * .5f);


    currentDirection.RotateSelfRad(ChangeInAngle);
    enVector2 CirclePosition = FuturePosition + (currentDirection * circleRadius);

    enVector2 FinalPosition = CirclePosition - FuturePosition;

    myBoid.m_currentWanderTime = minimumWanderTime;
    myBoid.setWander(true);
    std::cout << "wander state going to " << FinalPosition << '\n';

    return Boid::seek(myBoid, FinalPosition, desiredMagnitude);
  }

  return enVector2::zeroVector;
}

enVector2
Boid::followPath(Boid& myBoid,
                 enCircularLinkList<enNode>& nodes,
                 float desiredMagnitude,
                 sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = myBoid.m_nodeIndex.getIndex();
  enNode* ptrToNode = nodes.getPtr(currentIndex);

  if( myBoid.getDistanceTo(ptrToNode->m_position) < ptrToNode->m_radius )
  {
    myBoid.m_nodeIndex.incrementIndex();
    myBoid.m_nodeIndex.resetIfIndexEqualsMax(nodes.getSize());
    currentIndex = myBoid.m_nodeIndex.getIndex();
    //std::cout << "going to next node  = " << currentIndex << '\n';;
  }

  if( currentIndex == 0 )
  {
    result = Boid::seek(myBoid, ptrToNode->m_position, desiredMagnitude);
  }
  else
  {
    enNode* ptrToPreviousNode = nodes.getPtr(currentIndex - 1);

    const enVector2 directPathToNode = ptrToNode->m_position - myBoid.getPosition();

    const enVector2 pathBetweenNodes = enVector2(ptrToNode->m_position - ptrToPreviousNode->m_position);

    const enVector2 pathFromPreviousNodeToBoid = (myBoid.getPosition() - ptrToPreviousNode->m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);


    enVector2 finalPath = (correctionVector + directPathToNode);// + myBoid.getPosition();

    if( window != nullptr )
    {
      sf::VertexArray Line = sfHelp::CreateVisualLine(myBoid.getPosition(),
                                                      finalPath,
                                                      1.0f);


      window->draw(Line);
    }

    result = Boid::seek(myBoid, finalPath + myBoid.getPosition(), desiredMagnitude);
  }

  return result;
}

enVector2
Boid::patrol(Boid& myBoid,
             enCircularLinkList<enNode>& nodes,
             float desiredMagnitude,
             sf::RenderWindow* window)
{
  enVector2 result(enVector2::zeroVector);
  size_t currentIndex = myBoid.m_nodeIndex.getIndex();
  enNode* ptrToNode = nodes.getPtr(currentIndex);



  if( myBoid.getDistanceTo(ptrToNode->m_position) < ptrToNode->m_radius )
  {

    if( currentIndex == 0 )
    {
      myBoid.m_nodeIndex.setIncrementAmount(1);
    }
    else if( currentIndex == nodes.getSize() - 1 )
    {
      myBoid.m_nodeIndex.setIncrementAmount(-1);
    }

    myBoid.m_nodeIndex.incrementByIncrementAmount();
    currentIndex = myBoid.m_nodeIndex.getIndex();
    //std::cout << "going to next node  = " << currentIndex << '\n';;
  }

  if( currentIndex == 0 )
  {
    result = Boid::seek(myBoid, ptrToNode->m_position, desiredMagnitude);
  }
  else
  {
    enNode* ptrToPreviousNode = nodes.getPtr(currentIndex - 1);

    const enVector2 directPathToNode = ptrToNode->m_position - myBoid.getPosition();

    const enVector2 pathBetweenNodes = enVector2(ptrToNode->m_position - ptrToPreviousNode->m_position);

    const enVector2 pathFromPreviousNodeToBoid = (myBoid.getPosition() - ptrToPreviousNode->m_position);

    const enVector2 projectionOnPath = pathFromPreviousNodeToBoid.Projection(pathBetweenNodes);

    const enVector2 correctionVector = (projectionOnPath - pathFromPreviousNodeToBoid);

    enVector2 finalPath = (correctionVector + directPathToNode);// + myBoid.getPosition();

    if( window != nullptr )
    {
      sf::VertexArray Line = sfHelp::CreateVisualLine(myBoid.getPosition(),
                                                      finalPath,
                                                      1.0f);


      window->draw(Line);
    }

    result = Boid::seek(myBoid, finalPath + myBoid.getPosition(), desiredMagnitude);
  }

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

