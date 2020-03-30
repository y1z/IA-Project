#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"



class enMapReader
{
public:

  std::vector<sf::VertexArray> 
  ReadData(std::string_view data);

private:
  /**
  * @brief : search for the 'v' token
  */
  bool 
  searchForVertexData(std::string_view& data, std::vector<sf::VertexArray>& result);

  /**
  * @brief : process the value after the 'v' token
  */
  bool 
  readGeometryData(std::string_view& data, std::vector<sf::VertexArray>& result);

  /**
  * @brief : process the value pair example (100,100)
  */
  sf::Vertex
  readPosition(std::string_view& data, std::vector<sf::VertexArray>& result);

  /**
  * @brief : check if a given character is a number.
  */
  bool 
  CheckForNumberChar(char possibleNumber);
  



  enum ReaderMode
  {
    seachForVertex,
    readingGeometryData,
  };

  ReaderMode m_mode = ReaderMode::seachForVertex;

  /**
  * @brief : keep track of where we are inside the file.
  */
  size_t m_index = 0u;
};

