#pragma once
#include "cBaseApp.h"
#include "Boid.h"
#include "enPathNode.H"
#include "cFSM.h"
#include "enGrid.h"
#include "enRoom.h"

#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

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

private:

  /**
  * @returns : true if no error occurred.
  * @brief :updates anything that need to update.
  */
  bool
  update(float elapsedTime);


public:
  /**
  * @brief : create all the boid that will participate in the behaviors
  * @bug : no know bugs.
  */
  bool
  createAllBoids();

  /**
  * @brief : set all characteristics of the boids.
  * @bug :no known bugs.
  */
  bool 
  setAllBoids();

  /**
  * @brief : sets up the player.
  * @bug : no known bugs.
  */
  bool 
  setUpPlayer();

/**
* @brief : handles all events related with the window
* @bug : no known bugs
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
  * @brief : contains all the nodes for the follow path.
  * @bug : no known bugs.
  */
  enCircularLinkList<enPathNode>
  m_nodes;

  /**
  * @brief : this is the user controlled boid,it is not visible
  */
  Boid*
  m_pTarget = nullptr;

  /**
  * @brief : the player controlled boid.
  */
  std::unique_ptr<Boid>
  m_pPlayer = nullptr;

  std::unique_ptr<enRoom>
  m_pRoom = nullptr;


/**
* @brief : this is the window for the app
*/
  sf::RenderWindow*
  m_pWindow = nullptr;

/**
* @brief : this keep track of how much time has transpired
*/
  Timer* 
  m_pTimer = nullptr;

  /**
  * @brief : the finite state machine.
  * @bug :
  */
  cFSM*
  m_pFsm = nullptr;

  /**
  * @brief : it's a grid.
  */
  std::unique_ptr<enGrid> m_pGrid = nullptr;
  
};


