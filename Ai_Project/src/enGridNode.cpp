#include "..\include\enGridNode.h"

enGridNode::enGridNode()
{}

bool 
enGridNode::operator==(enGridNode const& other) const
{
  if( this->m_data.m_columnIndex == other.m_data.m_columnIndex &&
     this->m_data.m_rowIndex == other.m_data.m_rowIndex )
  {
    return true;
  }

  return false;
}

bool 
enGridNode::operator!=(enGridNode const& other) const
{

  if( this->m_data.m_columnIndex != other.m_data.m_columnIndex ||
     this->m_data.m_rowIndex != other.m_data.m_rowIndex )
  {
    return true;
  }

  return false;
}


void
enGridNode::init(int64_t columnIndex,
                 int64_t rowIndex,
                 enVector2& const worldPos,
                 int64_t cost,
                 sf::Color colorOfNode)
{
  m_data.m_columnIndex = columnIndex;
  m_data.m_rowIndex = rowIndex;
  m_data.m_worldPos = worldPos;
  m_data.m_costToTravers = cost;
  m_data.m_nodeColor = colorOfNode;
}

void 
enGridNode::setColor(sf::Color const newColor)
{
  m_data.m_nodeColor = newColor;
}

void 
enGridNode::setCost(int64_t cost)
{
  m_data.m_costToTravers = cost;
}

int64_t 
enGridNode::getCost() const
{
  return m_data.m_costToTravers;
}

sf::Color
enGridNode::getColor() const
{
  return m_data.m_nodeColor;
}

enVector2 
enGridNode::getPosition() const
{
  return m_data.m_worldPos;
}

int64_t 
enGridNode::getRowIndex() const
{
  return m_data.m_rowIndex;
}

int64_t
enGridNode::getColumnIndex() const
{
  return m_data.m_columnIndex;
}

std::array<int64_t, 2> const
enGridNode::getRowAndColumn() const
{
  std::array<int64_t, 2> const result =
  { this->m_data.m_rowIndex,
    this->m_data.m_columnIndex };

    return result;
}
