#pragma once
#include "cBaseApp.h"

#include <iostream>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Boid.h"

class enVector2;
class sf::RenderWindow;
class Timer;

/**
* @brief : this will contain a app for demonstrating all the steering behaviors
*/
class AppSteeringBehaviors final :
  public cBaseApp
{
public:
  AppSteeringBehaviors() = default;
  ~AppSteeringBehaviors() = default;
public:

  bool 
  init() override;

  int 
  run() override;

  void
  destroy() override;
private:
  std::vector<Boid> m_boids;

  enVector2* mptr_target = nullptr;
  sf::RenderWindow* mptr_window = nullptr;
  Timer* mptr_timer = nullptr;
};

