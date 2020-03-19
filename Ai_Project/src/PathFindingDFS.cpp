#include "..\include\PathFindingDFS.h"


bool
PathFindingDFS::createPath(enGrid& const grid,
                           const enGridNode& startingNode,
                           const enGridNode& endingNode)
{
  m_staringNode = startingNode;
  m_currentNode = startingNode;
  m_endingNode = endingNode;

  if( !PreReserveResource() )
  {
    return false;
  }

  std::array<int64_t, 2> const rowAndColumn = m_staringNode.getRowAndColumn();
  int64_t currentIndex = grid.getNodeIndex(rowAndColumn[1], rowAndColumn[0]);


  while( m_currentNode != m_endingNode )
  {

  }


  return true;
}

bool
PathFindingDFS::PreReserveResource()
{
  try
  {
    m_path.reserve(256);
    m_closed.reserve(256);
    m_open.reserve(256);
  }
  catch( const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

