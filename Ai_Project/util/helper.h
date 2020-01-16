#pragma once
#include "SFML/Main.hpp"
#include <cstdint>

namespace sfHelp
{

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
  * @brief :
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



}
