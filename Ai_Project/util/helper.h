#pragma once
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "enVector2.h"
#include "definitions.h"
#include <random>
#include <cstdint>

namespace sfHelp
{

  /**
  * @brief : changes the size of the sprite
  * @bug : no known bugs
  */
  static void
  Resize(sf::Sprite& sprite,
         uint32_t newSizeX,
         uint32_t newSizeY)
  {
    sf::IntRect const originalSize = sprite.getTextureRect();

    float const reprocipicalX = 1.0f / static_cast<float>(originalSize.width);
    float const reprocipicalY = 1.0f / static_cast<float>(originalSize.height);


    sf::Vector2f const originalScale = sprite.getScale();

    float const xScale = newSizeX * reprocipicalX * static_cast<float>(originalScale.x);
    float const yScale = newSizeY * reprocipicalY * static_cast<float>(originalScale.y);

    sprite.setScale(xScale, yScale);
  }

  /**
  * @brief :takes a vector then converts it to a sf::Vector2f
  * @param[in] myVector : the vector that going to be converted to
  * a sf::Vector2f
  * @bug :
  */
  static sf::Vector2f
  ConvertToSfmlVector(const enVector2& myVector)
  {
    return sf::Vector2f(myVector.X,myVector.Y);
  }

  /**
  * @brief : creates a line that can be represented on screen though
  *          a vertex sf::VertexArray
  * @param[in] StartPoint : where the line starts.
  * @param[in] endPoint : where the line ends.
  * @bug : no known bugs.
  */
  static sf::VertexArray
  CreateVisualLine(const enVector2& StartPoint,
                   const enVector2& endPoint,
                   float endPointScale = 10.0f)
  {
    sf::VertexArray result(sf::PrimitiveType::Lines);

    result.append(ConvertToSfmlVector(StartPoint));
    result.append(ConvertToSfmlVector(StartPoint + (endPoint * endPointScale)));

    return result; 
  }


  static sf::CircleShape
  CreateCircle(const enVector2& Point,
               float radius = 100.0f)
  {
    sf::CircleShape result(radius);
    sf::IntRect const circulOrigin = result.getTextureRect();
    result.setOrigin(circulOrigin.width * .5f,
                     circulOrigin.height * .5f); 

    result.setPosition(ConvertToSfmlVector(Point));


    return result;
  }

  /**
  * @brief : generates a value from the range (minimum ... maximum)
  * @return : a value from the range (minimum ... maximum)
  * param[in] minimum : the minimum return value.
  * param[in] maximum : the maximum return value.
  * @bug : no known bugs
  */
  static int32_t 
  RandIntRange(int32_t minimum, int32_t maximum)
  {
    static bool isSeeded = false;
    if( isSeeded == false )
    {
      srand(time(nullptr));
      isSeeded = true;
    }

    int32_t const difference = std::max(maximum, minimum) - std::min(maximum, minimum);
    float const percentage = (rand()) / static_cast<float>(RAND_MAX);

    return minimum + (difference * percentage);
  }

  /**
  * @brief : generates a value from the range (minimum ... maximum)
  * @return : a value from the range (minimum ... maximum)
  * param[in] minimum : the minimum return value.
  * param[in] maximum : the maximum return value.
  * @bug : no known bugs
  */
  static float 
  RandFloatRange(float minimum,float maximum)
  {
    static bool isSeeded = false;
    static std::mt19937 numberGenerator;

    if( isSeeded == false )
    {
      std::random_device rd;
      std::seed_seq const seeds = { rd(),rd(),rd(),rd(),rd(),rd() };
      numberGenerator.seed(seeds);
      isSeeded = true;
    }

    float const differenceBetweenValues = std::max(maximum, minimum) - std::min(maximum, minimum);
    float const percentage = numberGenerator() / static_cast<float>(numberGenerator.max());

    return minimum + (differenceBetweenValues * percentage);
  }

}
