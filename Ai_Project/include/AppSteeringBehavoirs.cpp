#include "AppSteeringBehavoirs.h"
#include "Timer.h"
#include "CVector2D.h"
#include "helper.h"

bool
AppSteeringBehaviors::init()
{
  m_boids.emplace_back();
  m_boids.emplace_back();

  for (Boid& boid : m_boids) {
    if (!boid.loadSprite("../resources/sprites/S_generic_boid.png"))
    {
      return false;
    }
    boid.setPosition(1000.0f, 1000.0f);
    sfHelp::Resize(boid.m_sprite, 35u * 5u, 25u * 5u);
  }


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

    this->windowEvents();

    for (size_t i = 0; i < m_boids.size(); ++i)
    {
      enVector2 delta;
      if (i % 2 == 0) {
        delta += Boid::seek(m_boids[i].m_position, mptr_target->m_position, 1.0f);
      }
      else 
      {
        delta += Boid::flee(m_boids[i].m_position, mptr_target->m_position, 1.0f, 500.0f);
      }

      m_boids[i].m_position += delta * m_boids[i].getSpeed() * mptr_timer->GetResultSecondsFloat();

      m_boids[i].update();
      m_boids[i].m_sprite.setPosition(m_boids[i].m_position.X, m_boids[i].m_position.Y);
    }


    mptr_window->clear();
    for (const Boid& boid : m_boids)
    {
      mptr_window->draw(boid.m_sprite);
    }
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

void
AppSteeringBehaviors::windowEvents()
{

  sf::Event event;
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
}
