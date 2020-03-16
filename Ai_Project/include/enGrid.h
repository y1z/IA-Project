#pragma once
#include <vector>
#include <cstdint>
#include "enVector2.h"
#include "enGridNode.h"
#include <SFML/Graphics.hpp>

class enGrid
{
public:
	enGrid();

	~enGrid() = default;



public:

  /**
  * @brief : create's a grid 
  * @param[in] widthOfGrid : controls how many 
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
  * @param[in] row : which row is the node located at.
  * @param[in] column : which column is the node located at.
  * @bug : no known bugs.
  */
  bool
  checkIfInBound(int64_t column,
                 int64_t row);

  /**
  * @returns: the index where a particular node is located.
  */
  int64_t
  getNodeIndex(int64_t column,
               int64_t row);

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
  * @brief : represents the grid. 
  */
	std::vector<enGridNode> m_gridNodes;
};

