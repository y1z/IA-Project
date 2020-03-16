#pragma once
#include <cstdint>
#include "enVector2.h"
#include <SFML/Graphics.hpp>

class enGridNode
{
public:
  enGridNode();

  ~enGridNode() = default;
public:

  /**
  * @brief : defines the properties of the GridNode.
  * @param[in] columnIndex :what column does the node belong to.
  * @param[in] rowIndex :what row does the node belong to.
  * @param[in] worldPos: the location of the node in world-space.
  * @param[in] cost : how hard it is to move through the node.
  * @param[in] colorOfNode : what color the node has (used to indicate information
  * about the node).
  */
  void
  init(int64_t columnIndex,
       int64_t rowIndex,
       enVector2& const worldPos,
       int64_t cost = 1,
       sf::Color colorOfNode = sf::Color::White);


public:

  /**
  * @brief : which column does this node belong to .
  */
  int64_t m_columnIndex;

  /**
  * @brief : which row does this node belong to .
  */
  int64_t m_rowIndex;

  /**
  * @brief : represents how difficult it's going to move
  * to the particular node.
  */
  int64_t m_costToTravers = 1;

  /**
  * @brief : where the node is in the world-space.
  */
  enVector2 m_worldPos;

  /**
  * @brief : the color of the individual node.
  */
  sf::Color m_nodeColor = sf::Color::White;
};

