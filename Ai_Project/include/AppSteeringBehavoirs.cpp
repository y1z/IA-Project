#include "AppSteeringBehavoirs.h"
#include "Timer.h"
#include "CVector2D.h"
#include "helper.h"

bool
AppSteeringBehaviors::init()
{
  m_boids.emplace_back();
  m_boids.emplace_back();

  m_boids[0].loadSprite("../resources/sprites/S_generic_boid.png");
  m_boids[0].setPosition(1000, 1000);

  sfHelp::Resize(m_boids[0].m_sprite, 35u * 10, 25u * 10);

  mptr_target = new Boid(2000, 200);
  mptr_window = new sf::RenderWindow(sf::VideoMode(2000, 2000), " Boids behaviors ");
  mptr_timer = new Timer();

  return true;
}

int
AppSteeringBehaviors::run()
{
  while (mptr_window->isOpen())
  {
    mptr_timer->StartTiming();
    sf::Event event;
    enVector2 delta = Boid::seek(m_boids[0].m_position,  mptr_target->m_position , 1.0f);//Boid::arrival(m_boids[0].m_position, *mptr_target, 1.0f,500.0f);//Boid::seek(m_boids[0].m_position, *mptr_target, 1.0f) +
      //Boid::flee(m_boids[0].m_position, *mptr_target, 1.1f, 1000.0f);


    while (mptr_window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        mptr_window->close();

      if (event.type == sf::Event::KeyPressed)
      {

      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
        sf::Vector2i position = sf::Mouse::getPosition(*mptr_window);

        mptr_target->setPosition(position.x, position.y);
      }
    }
    m_boids[0].m_position += delta * m_boids[0].getSpeed() * mptr_timer->GetResultSecondsFloat();

    m_boids[0].update();
    mptr_window->clear();
    m_boids[0].m_sprite.setPosition(m_boids[0].m_position.X, m_boids[0].m_position.Y);
    mptr_window->draw(m_boids[0].m_sprite);
    mptr_window->display();

    mptr_timer->EndTiming();
  }
  // TODO: add everthing needed to run the app
  return 0;
}

void
AppSteeringBehaviors::destroy()
{
  if (mptr_target != nullptr) {
    delete mptr_target;
    mptr_target = nullptr;
  }

  if (mptr_window != nullptr) {
    delete  mptr_window;
    mptr_window = nullptr;
  }

  if (mptr_timer != nullptr) {
    delete mptr_timer;
    mptr_timer = nullptr;
  }

}
