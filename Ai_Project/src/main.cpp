#include <iostream>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include "AppSteeringBehavoirs.h"


/***
* Forward declarations
*/



int
main()
{
  cBaseApp* ptr_app = new AppSteeringBehaviors();
  ptr_app->init();
  int result = ptr_app->run();
  ptr_app->destroy();

  return  result;
  //Timer timer;
  //Boid seeker;

  //enVector2 Target(1000, 1000);

  //seeker.loadSprite("../resources/sprites/S_flee.png");

  //sf::RenderWindow window(sf::VideoMode(2000, 2000), "SFML works!");
  //sf::CircleShape shape(300.f);
  //shape.setFillColor(sf::Color::Green);
  //seeker.m_sprite.setPosition(sf::Vector2f(0.0f,0.0f));


  //while (window.isOpen())
  //{
  //  timer.StartTiming();
  //  sf::Event event;
  //  while (window.pollEvent(event))
  //  {
  //    if (event.type == sf::Event::Closed)
  //      window.close();

  //    if (event.type == sf::Event::KeyPressed) 
  //    {
  //      if(event.key.code == sf::Keyboard::Num1)
  //      {
  //        
  //      }
  //    }
  //  }
  //  seeker.m_position += Boid::seek(seeker.m_position, Target, 1.0f ) * timer.GetResultSecondsFloat() * seeker.getSpeed();

  //  window.clear();
  //  window.draw(shape);
  //  seeker.m_sprite.setPosition(seeker.m_position.X, seeker.m_position.Y);
  //  window.draw(seeker.m_sprite);
  //  window.display();

  //  timer.EndTiming();
  //}




  return 0;
}

