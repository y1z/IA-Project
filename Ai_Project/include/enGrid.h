#pragma once
#include <deque>
#include <cstdint>
#include "enVector2.h"
#include "enGridNode.h"
#include <SFML/Graphics.hpp>

  /**
  * @brief : represents a grid 
  */
class enGrid
{
public:
	enGrid();

	~enGrid() = default;



public:

  /**
  * @brief : create's a grid.
  * @param[in] widthOfGrid : controls how many columns the grid has per row.
  * @param[in] heighOfGrid : controls how many rows the grid has per columns.
  * @param[in] heighOfWorld : the total width of the grid.
  * @param[in] heighOfGrid :  the total height of the grid.
  */
  bool 
  init(int64_t widthOfGrid,
       int64_t heightOfGrid,
       float widthOfWorld,
       float heightOfWorld);

  /**
  * @brief : draw every single node in the grid.
  */
  void
  drawGrid(sf::RenderWindow &window);

private:
  /**
  * @brief : check if the grid is within the size requirements.
  * @returns : true if the size Requirements are met, false if not.
  */
  bool 
  checkSizeRequirements(int64_t widthOfGrid,
                        int64_t heightOfGrid,
                        float widthOfWorld,
                        float heightOfWorld);

  /**
  * @note : the first index is 0,0
  * @retuns : true if the row and column index exist in the grid; false otherwise.
  * @param[in] column : which column is the node located at.
  * @param[in] row : which row is the node located at.
  * @bug : no known bugs.
  */
  bool
  checkIfInBound(int64_t column,
                 int64_t row) const;

public:
  /**
  * @returns: the index where a particular node is located or -1 when the node 
  * does not exist.
  * @bug : no known bugs.
  */
  int64_t
  getNodeIndex(int64_t column,
               int64_t row) const;

  /**
  * @retuns : a pointer to a node.
  * @bug : no known bugs.
  */
  enGridNode*
  getNodePtrByIndex(int64_t nodeIndex);

  /**
  * @retuns : a copy of a node
  * @bug : no known bugs.
  */
  enGridNode
  getNodeByIndex(int64_t nodeIndex) const;

  /**
  * @returns :the container of the grid.
  * @bug : no known bugs.
  */
  std::deque<enGridNode>& const
  getGridRef();

private:

  /**
  * @brief : will be used to contain all the information needed to draw 
  * every node.
  */
  sf::RectangleShape m_sharedRactangle;

  /**
  * @brief : the size of every rectangle of every node.
  */
  sf::Vector2f m_sharedSizeOfRectangle;
private:

  /**
  * @brief : controls the minimum size of a grid
  */
  constexpr static int64_t s_minimumGridDimensions = 4;

  /**
  * @brief : controls the minimum size of the world the grid will accept
  */
  constexpr static float s_minimumWorldDimensions = 10.0f;

private:
  /**
  * @brief : keeps track of how-many columns there are in total
  */
  int64_t m_columnTotal;

  /**
  * @brief : keeps track of how-many rows there are in total
  */
  int64_t m_rowTotal;

  /**
  * @brief : how many columns every row has.
  */
  int64_t m_Pitch;


  /**
  * @brief : contains the grid itself. 
  */
	std::deque<enGridNode> m_gridNodes;
};

