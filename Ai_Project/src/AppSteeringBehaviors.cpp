#include "AppSteeringBehaviors.h"
#include "Timer.h"
#include "enVector2D.h"
#include "helper.h"
#include <cstdint>
#include <string>
#include <random>

static constexpr uint32_t minimumWidth = 35u;
static constexpr uint32_t minimumHeight = 25u;

static constexpr uint32_t s_totalBoids = 2u;


bool
AppSteeringBehaviors::init()
{

  mptr_target = new Boid(200, 200);
  mptr_window = new sf::RenderWindow(sf::VideoMode(2000, 2000),
                                     " Boids behaviors ");
  mptr_timer = new Timer();

  for( size_t i = 0; i < s_totalBoids; ++i )
  {
    m_boids.emplace_back();
  }

  for( size_t i = 0; i < 5; ++i )
  {
    m_nodes.emplace_back(enNode(enVector2(minimumWidth * 3.5 * i, minimumHeight * 5 * i)));
  }

  uint32_t Difference = 0;


  for( Boid& boid : m_boids )
  {
    if( !boid.loadSprite("../resources/sprites/S_generic_boid.png") )
    {
      return false;
    }
    boid.setSpeed(100.0f);
    boid.setPosition(mptr_window->getSize().x / 6 + Difference, mptr_window->getSize().y / 2);
    sfHelp::Resize(boid.m_sprite, minimumWidth * 5u, minimumHeight * 5u);
    Difference += minimumWidth * 5u * 2;
  }

  return true;
}

int
AppSteeringBehaviors::run()
{
  while( mptr_window->isOpen() )
  {
    mptr_window->clear();
    mptr_timer->StartTiming();

    this->windowEvents();

    for( size_t i = 0; i < m_boids.size(); ++i )
    {
      enVector2 resultingForce;
      if( i % 5 == 0 )
      {
        resultingForce += Boid::seek(m_boids[i], *mptr_target, 4.5f);
      }

      else if( i % 5 == 1 )
      {
        resultingForce += Boid::followPath(m_boids[i],
                                           m_nodes,
                                           5.0f);
      }

      //else if( i % 5 == 2 )
      //{
      //  resultingForce += Boid::evade(m_boids[i],
      //                                m_boids[i - 2],
      //                                2.0f,
      //                                4.6f,
      //                                500.0f);
      //}

      //else if( i % 5 == 3 )
      //{
      //  resultingForce += Boid::flee(m_boids[i],
      //                               m_boids[i - 3].m_position,
      //                               2.0f,
      //                               500.0f);
      //}

      //else if( i % 5 == 4 )
      //{
      //  resultingForce += Boid::arrive(m_boids[i],
      //                                 mptr_target->m_position,
      //                                 3.0f,
      //                                 200.0f);
      //}

      resultingForce *= m_boids[i].getSpeed() * mptr_timer->GetResultSecondsFloat();
      m_boids[i].addForce(resultingForce);

      m_boids[i].update();

      m_boids[i].m_sprite.setPosition(m_boids[i].m_position.X, m_boids[i].m_position.Y);
    }


    for( const Boid& boid : m_boids )
    {
      mptr_window->draw(boid.m_sprite);
    }
    mptr_window->display();

    mptr_timer->EndTiming();
  }

  return 0;
}

void
AppSteeringBehaviors::destroy()
{
  if( mptr_target != nullptr )
  {
    delete mptr_target;
    mptr_target = nullptr;
  }

  if( mptr_window != nullptr )
  {
    delete  mptr_window;
    mptr_window = nullptr;
  }

  if( mptr_timer != nullptr )
  {
    delete mptr_timer;
    mptr_timer = nullptr;
  }

}

void
AppSteeringBehaviors::windowEvents()
{

  sf::Event event;
  while( mptr_window->pollEvent(event) )
  {
    if( event.type == sf::Event::Closed )
      mptr_window->close();

    if( event.type == sf::Event::MouseButtonPressed )
    {
      sf::Vector2i position = sf::Mouse::getPosition(*mptr_window);

      mptr_target->setPosition(position.x, position.y);
    }

    if( event.type == sf::Event::KeyPressed )
    {
      sf::View currentViewPort = mptr_window->getView();

      if( event.key.code == sf::Keyboard::W )
      {
        currentViewPort.move(sf::Vector2f(0.0f, -100.0f));
        mptr_window->setView(currentViewPort);
      }
      if( event.key.code == sf::Keyboard::S )
      {
        currentViewPort.move(sf::Vector2f(0.0f, 100.0f));
        mptr_window->setView(currentViewPort);
      }
      if( event.key.code == sf::Keyboard::A )
      {
        currentViewPort.move(sf::Vector2f(-100.0f, 0.0f));
        mptr_window->setView(currentViewPort);
      }
      if( event.key.code == sf::Keyboard::D )
      {
        currentViewPort.move(sf::Vector2f(100.0f, 0.0f));
        mptr_window->setView(currentViewPort);
      }

    }

  }
}
