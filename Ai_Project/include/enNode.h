#pragma once
#include "enVector2D.h"

class enNode
{
public:
  enNode();
  enNode(const enVector2 &position, float radius = 100.0f);
  ~enNode() = default;
public:
  /**
  * @brief : used to know where the position of the node is.
  */
  enVector2
  m_position;

  /**
  * @brief : used to know how close to get to a node before it considered visited
  */
  float
  m_radius;

  /**
  * @brief : used to know if the node is already visited.
  */
  bool
  is_visited = false;

private:

};

