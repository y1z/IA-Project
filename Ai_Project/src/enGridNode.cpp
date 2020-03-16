#include "..\include\enGridNode.h"

enGridNode::enGridNode()
  :m_columnIndex(0),
  m_rowIndex(0),
  m_worldPos(enVector2::zeroVector),
  m_costToTravers(1),
  m_nodeColor(sf::Color::White)
{}


void
enGridNode::init(int64_t columnIndex,
                 int64_t rowIndex,
                 enVector2& const worldPos,
                 int64_t cost,
                 sf::Color colorOfNode)
{
  m_columnIndex = columnIndex;
  m_rowIndex = rowIndex;
  m_worldPos = worldPos;
  m_costToTravers = cost;
  m_nodeColor = colorOfNode;
}
