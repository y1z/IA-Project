#include "..\include\enRoom.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool 
enRoom::readFile(std::string_view filePath)
{
  std::ifstream inputFile(filePath.data());

  if( inputFile.is_open() )
  {
    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string data = ss.str();

    m_geometryData = m_mapReader.ReadData(data);

  }
  else
  {
    std::cerr << "failed to read path [" << filePath << "]\n";
    return false;
  }

  return true;
}

void
enRoom::draw(sf::RenderWindow& window)
{

  for( auto& geomtry : m_geometryData )
  {
    window.draw(geomtry);
  }

}
