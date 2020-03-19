#pragma once
#include "enGrid.h"
#include <vector>
#include <deque>


struct sPathFindingData
{
  enGridNode* m_node = nullptr;
  bool is_visited = false;
};

  /**
  * @brief : the interface for each type of Path finding technique.
  * @bug : no known bugs.
  */
class enPathFindingBase
{
public:
  enPathFindingBase() = default;
  enPathFindingBase(enPathFindingBase&&other) noexcept = default;
  enPathFindingBase(const enPathFindingBase&other) = delete;
	virtual ~enPathFindingBase() = default;

public:

  /**
  * @brief : create a path from a staring node to a ending node.
  * @returns : true if it was successful.
  * @param[in] grid : the grid where the path will be formed.
  * @bug : no known bugs.
  */
  virtual bool
  createPath(enGrid& const grid,
             const enGridNode& startingNode,
             const enGridNode& endingNode) = 0;

  /**
  * @returns a reference to the resulting path.
  * @bug : no known bugs.
  */
  std::vector <enGridNode*>&
  getPathRef();
protected:

  /**
  * @brief : used to reserve resource before stating to create the path.
  * @bug : no known bugs.
  */
  virtual bool
  PreReserveResource() = 0;
           

public:
  /**
  * @brief : the path generated from the pathFinding algorithm.
  */
	std::vector <enGridNode*> m_path;

protected:
  /**
  * @brief : nodes that could be added to the path.
  */
	std::vector <enGridNode*> m_open;

  /**
  * @brief : nodes that have already 
  */
	std::vector <enGridNode*> m_closed;

  /**
  * @brief : the starting point for the 
  */
  enGridNode m_staringNode;

  enGridNode m_endingNode;

  enGridNode m_currentNode;

  enGridNode m_prevNode;
};

