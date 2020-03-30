#pragma once
#include "SFML/Graphics.hpp"
#include <string_view>
#include <vector>

#include "enMapReader.h"


class enRoom
{
public:

  /**
  * @brief : read a file that contains the information for making a room.
  * @bug : no known bugs.
  */
  bool 
  readFile(std::string_view filePath);

  /**
  * @brief : draws all the geometry in the room.
  * @bug : no known bugs
  */
  void 
  draw(sf::RenderWindow &window);

  std::vector<sf::VertexArray> m_geometryData;

  enMapReader m_mapReader;
};

