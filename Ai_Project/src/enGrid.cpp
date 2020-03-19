#include "enGrid.h" 
#include "definitions.h"
#include "helper.h"

enGrid::enGrid()
  :m_columnTotal(4),
  m_rowTotal(4),
  m_Pitch(4)
{}

bool
enGrid::init(int64_t const widthOfGrid,
             int64_t const heightOfGrid,
             float widthOfWorld,
             float heightOfWorld)
{
  bool const areSizeRequirementMet = this->checkSizeRequirements(widthOfGrid,
                                                                 heightOfGrid,
                                                                 widthOfWorld,
                                                                 heightOfWorld);

  if( areSizeRequirementMet == false )
    return false;

  float const distancePerNodeInX = widthOfWorld / widthOfGrid;
  float const distancePerNodeInY = heightOfWorld / heightOfGrid;

  m_sharedSizeOfRectangle.x = distancePerNodeInX * .9f;
  m_sharedSizeOfRectangle.y = distancePerNodeInY * .9f;

  m_sharedRactangle.setSize(m_sharedSizeOfRectangle);

  m_sharedRactangle.setOrigin(m_sharedSizeOfRectangle.x * .5f,
                              m_sharedSizeOfRectangle.x * .5f);

  m_Pitch = widthOfGrid;

  for( int64_t i = 0; i < heightOfGrid; i++ )
  {
    for( int64_t j = 0; j < widthOfGrid; j++ )
    {
      enVector2 worldPosForNode(distancePerNodeInX * (j + 1),
                                distancePerNodeInY * (i + 1));
      enGridNode node;
      node.init(j, i, worldPosForNode);
      m_gridNodes.emplace_back(node);
    }
  }

  return true;
}

void
enGrid::drawGrid(sf::RenderWindow& window)
{

  for( enGridNode& node : m_gridNodes )
  {
    m_sharedRactangle.setFillColor(node.getColor());
    m_sharedRactangle.setPosition(sfHelp::ConvertToSfmlVector(node.m_data.m_worldPos));
    window.draw(m_sharedRactangle);
  }

}

bool
enGrid::checkSizeRequirements(int64_t widthOfGrid,
                              int64_t heightOfGrid,
                              float widthOfWorld,
                              float heightOfWorld)
{
  if( widthOfGrid < s_minimumGridDimensions )
  {
    LOG_MSG("The grid in NOT wide enough");
    return false;
  }

  if( heightOfGrid < s_minimumGridDimensions )
  {
    LOG_MSG("The grid in NOT tall enough");
    return false;
  }

  if( widthOfWorld < s_minimumWorldDimensions )
  {
    LOG_MSG("the world needs to be wider");
    return false;
  }

  if( heightOfWorld < s_minimumWorldDimensions )
  {
    LOG_MSG("the world needs to be taller");
    return false;
  }
  return true;
}

bool
enGrid::checkIfInBound(int64_t column,
                       int64_t row) const
{
  if( !((m_rowTotal - 1) <= row) || (row < 0) )
  {
    LOG_MSG("the row goes out of range");
    return false;
  }

  if( !((m_columnTotal - 1) <= column) || (column < 0) )
  {
    LOG_MSG("the column goes out of range");
    return false;
  }
  return true;
}

int64_t
enGrid::getNodeIndex(int64_t column,
                     int64_t row)const
{
  int64_t result = -1;
  if( checkIfInBound(column, row) )
  {
    result = (m_Pitch * row) + column;
  }

  return result;
}

enGridNode*
enGrid::getNodePtrByIndex(int64_t nodeIndex)
{
  if( nodeIndex < m_gridNodes.size() && nodeIndex > -1 )
  {
    return &m_gridNodes[nodeIndex];
  }
  return nullptr;
}

enGridNode 
enGrid::getNodeByIndex(int64_t nodeIndex) const
{
  enGridNode result;
  if( nodeIndex < m_gridNodes.size() && nodeIndex > -1 )
  {
    result = m_gridNodes[nodeIndex];
    return result;
  }

  return  result;
}

std::deque<enGridNode>& const
enGrid::getGridRef() 
{
  return m_gridNodes;
}
