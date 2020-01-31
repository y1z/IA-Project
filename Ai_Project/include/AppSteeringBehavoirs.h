#pragma once
#include "cBaseApp.h"
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

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
* @bug : no know bugs.
*/
  int 
  run() override;

/**
* @brief : free all resource that where acquired
* @bug : no know bugs.
*/
  void
  destroy() override;
public:
/**
* @brief : handles all events related with the window
* @bug : when moving the camera the boids don't go 
*        to where the user clicks on screen.
*/
  void
  windowEvents();

private:
/**
* @brief : contains the boids used for the app
*/
  std::vector<Boid>
  m_boids;
/**
* @brief : this is the user controlled boid,it is not visible
*/
  Boid*
  mptr_target = nullptr;

/**
* @brief : this is the window for the app
*/
  sf::RenderWindow*
  mptr_window = nullptr;

/**
* @brief : this keep track of how much time has transpired
*/
  Timer* 
  mptr_timer = nullptr;
};


