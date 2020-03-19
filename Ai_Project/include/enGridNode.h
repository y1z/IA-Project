#pragma once
#include <cstdint>
#include <array>
#include "enVector2.h"
#include <SFML/Graphics.hpp>

  /**
  * @brief : contains all data the node handles.
  */
struct enGridNodeData
{
  enGridNodeData()
  :m_columnIndex(-1),
  m_rowIndex(-1),
  m_costToTravers(1),
  m_worldPos(enVector2::zeroVector),
  m_nodeColor(sf::Color::White)
  {}
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



  /**
  * @brief : represent the smallest representation 
  */
class enGridNode
{
public:
  enGridNode();

  ~enGridNode() = default;
public:

  bool operator ==(enGridNode const & other) const;
  bool operator !=(enGridNode const & other) const;

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


  void
  setColor(sf::Color const newColor);

  void 
  setCost(int64_t cost);
  

  /**
  * @returns : the cost of moving to the node.
  */
  int64_t 
  getCost() const;
  
  /**
  * @returns : the color of the node.
  */
  sf::Color
  getColor() const;

  /**
  * @returns : position of the GridNode.
  */
  enVector2
  getPosition()const;

  /**
  * @return : the row where the gridNode is.
  * @bug :
  */
  int64_t 
  getRowIndex()const;
  
  /**
  * @return : the column where the gridNode is.
  */
  int64_t 
  getColumnIndex()const;


  std::array<int64_t, 2> const
  getRowAndColumn() const;

public:

  enGridNodeData m_data;
};

