#pragma once
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "enVector2D.h"
#include "definitions.h"
#include <random>
#include <cstdint>

namespace sfHelp
{
  /**
  * @brief : used to scale a image to a specific size.
  * @returns :a vector which represent the new scale.
  * @bug : no known bugs
  */
  static sf::Vector2f
  ReScale(sf::Vector2u& originalScale,
          uint32_t newSizeX,
          uint32_t newSizeY)
  {

    float xScale = newSizeX / (float)originalScale.x;;
    float yScale = newSizeY / (float)originalScale.y;;

    return sf::Vector2f(xScale, yScale);
  }


  /**
  * @brief : changes the size of the sprite
  * @bug : no known bugs
  */
  static void
  Resize(sf::Sprite& sprite,
         uint32_t newSizeX,
         uint32_t newSizeY)
  {
    sf::IntRect originalSize = sprite.getTextureRect();

    float reprocipicalX = 1.0f / static_cast<float>(originalSize.width);
    float reprocipicalY = 1.0f / static_cast<float>(originalSize.height);


    sf::Vector2f originalScale = sprite.getScale();

    float xScale = newSizeX * reprocipicalX * static_cast<float>(originalScale.x);
    float yScale = newSizeY * reprocipicalY * static_cast<float>(originalScale.y);

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
    //sf::Vector2f circulOrigin = result.getOrigin();
    //result.setOrigin(circulOrigin.x * .5f,
    //                 circulOrigin.y * .5f);

    result.setPosition(ConvertToSfmlVector(Point));


    return result;
  }

  static int32_t 
  RandIntRange(int32_t minimum, int32_t maximum)
  {
    static bool isSeeded = false;
    if( isSeeded == false )
    {
      srand(time(nullptr));
      isSeeded = true;
    }

    int32_t const range = maximum - minimum;
    float const percentage =  static_cast<float>(rand()) / (RAND_MAX) + 1.0f;

    return  minimum + (range * std::clamp(percentage,0.0f,1.0f));
  }

}
