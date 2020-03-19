#pragma once
#include "enPathFindingBase.h"

class PathFindingDFS :
  public enPathFindingBase
{
public:
  PathFindingDFS() = default;
  PathFindingDFS(PathFindingDFS&& other)noexcept = default;
  PathFindingDFS(const PathFindingDFS & other) = delete;
  ~PathFindingDFS() = default;

public:

  /**
  * @brief : create a path from a staring node to a ending node.
  * @returns : true if it was successful.
  * @param[in] grid : the grid where the path will be formed.
  * @bug : no known bugs.
  */
  bool
  createPath(enGrid& const grid,
             const enGridNode& startingNode,
             const enGridNode& endingNode) override;

  /**
  * @brief : used to reserve resource before stating to create the path.
  * @bug : no known bugs.
  */
  bool 
  PreReserveResource(); 


};

