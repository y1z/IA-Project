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
/**
* @brief : starts by acquiring the resources for the app.
* @bugs : no know bugs.
*/
  bool 
  init() override;
/**
* @brief : this is the main loop for the app.
* @bugs : no know bugs.
*/
  int 
  run() override;

/**
* @brief : free all resource that where acquired
* @bugs : no know bugs.
*/
  void
  destroy() override;
public:
/**
* @brief :
* @bugs :
*/

  void
    windowEvents();

private:
  std::vector<Boid> m_boids;

  Boid* mptr_target = nullptr;
  sf::RenderWindow* mptr_window = nullptr;
  Timer* mptr_timer = nullptr;
};

