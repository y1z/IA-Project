#pragma once
#include "Boid.h"
#include "GlobalVariable.h"
#include <cstdint>
#include <vector>
  /**
  * @brief : used to known which state is the boid currently in.
  * @bug : no known bugs.
  */
enum class stateFlags : int32_t
{
  idle = 0,
  seek = 1,
  flee = 2,
  wander,

  SIZE
};

/**
*  struct
*/

struct sBoidPtrAndState
{
  BoidPtr  ptrToBoid = nullptr;
  stateFlags boidState = stateFlags::idle; 
  void *  ptrToStateDescriptor = nullptr;
  bool hasEntered = false;
};


struct seekStateArgs
{
  BoidPtr m_target;
  float m_magnitude = 1.0f;
  float m_radiusUtilStateChange = 50.0f;
};


struct fleeStateArgs
{
  BoidPtr m_target;
  float m_radiusUtilSafe = 100.0f;
  float m_magnitude = 1.0f;
};


struct idleStateArgs
{
  std::vector<sBoidPtrAndState>* m_boids = nullptr;
  float m_maximumIdleTime = 3.0f;
  float m_radiusUtilStateChange = 500.0f;
};


struct wanderStateArgs
{
  float m_magnitude = 1.0f;
  float m_circleRadius = 100.0f;
  float m_wanderingTime = 1.0f;
  float m_perditionTime = 5.0f;
  float m_angle = gvars::halfPi;
};



struct VectorAndID
{
  VectorAndID() = default;
  VectorAndID(uint32_t id, enVector2& Vector)
  :ID(id),
  force(Vector)
  {}

  uint32_t ID;
  enVector2 force;
};


/**
*  DEBUG MACROS
*/

#ifndef NDEBUG
#define LOG_MSG(message) std::cout << message << '\n';
#else
#define LOG_MSG(message)
#endif // !NDEBUG

