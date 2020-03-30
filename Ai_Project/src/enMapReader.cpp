#include "..\include\enMapReader.h"
#include "enVector2.h"
#include "helper.h"

static constexpr const char* s_validChars = "0123456789.";

bool
enMapReader::CheckForNumberChar(char possibleNumber)
{
  size_t index = 0;
  while( s_validChars[index] != 0 )
  {
    if( possibleNumber == s_validChars[index] )
      return true;
    index++;
  }

  return false;
};



std::vector<sf::VertexArray>
enMapReader::ReadData(std::string_view data)
{
  std::vector<sf::VertexArray> result;

  while( data.size() - 1 > m_index )
  {
    bool ReadGeoData = false;
    if( m_mode == ReaderMode::seachForVertex )
    {
      ReadGeoData = this->searchForVertexData(data, result);
    }

    if( ReadGeoData == true )
    {
      this->readGeometryData(data, result);
    }

    ++m_index;
  }

  m_index = 0;
  return result;
}

bool
enMapReader::searchForVertexData(std::string_view& data, std::vector<sf::VertexArray>& result)
{
  while( data.size() - 1 > m_index )
  {
    if( data.at(m_index) == 'v' )
    {
      ++m_index;
      return true;
    }

    ++m_index;
  }


  return false;;
}

bool 
enMapReader::readGeometryData(std::string_view& data,
                              std::vector<sf::VertexArray>& result)
{
  static constexpr const char* s_terminationChar = "|";


  sf::VertexArray additionalArray;
  additionalArray.setPrimitiveType(sf::PrimitiveType::LineStrip);

  while( data.size() > m_index )
  {
    sf::Vertex vert;

    if( this->CheckForNumberChar(data[m_index]) )
    {
      vert = this->readPosition(data, result);
      additionalArray.append(vert);
    }

    else if( data[m_index] == s_terminationChar[0] )
    {
      result.emplace_back(additionalArray);
      return true;
    }

    ++m_index;
  }
  return true;
}

sf::Vertex
enMapReader::readPosition(std::string_view& data,
                          std::vector<sf::VertexArray>& result)
{
  std::string Buffer;
  int vectorIndex = 0;
  enVector2 resultingPosition;
  
  while( data.size() - 1 > m_index )
  {
    if( this->CheckForNumberChar(data[m_index]) )
      Buffer.push_back(data[m_index]);

    else if(Buffer.size() > 0 )
    {
      resultingPosition.Array[vectorIndex] = std::stof(Buffer);
      Buffer.clear();
      vectorIndex++;
    }

    if( vectorIndex > 1 )
    {
      vectorIndex = 0;
      break;
    }

    ++m_index;
  }

  return sf::Vertex(sfHelp::ConvertToSfmlVector(resultingPosition));
}


