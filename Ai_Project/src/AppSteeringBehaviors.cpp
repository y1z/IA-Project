#include "AppSteeringBehaviors.h"
#include "Timer.h"
#include "enVector2.h"
#include "helper.h"
#include "GlobalVariable.h"

#include <cstdint>
#include <string>
#include <random>

static constexpr uint32_t s_minimumWidth = 35u;
static constexpr uint32_t s_minimumHeight = 25u;
static constexpr uint32_t s_totalBoids = 5u;


bool
AppSteeringBehaviors::init()
{
  mp_target = new Boid(200, 200);
  mp_window = new sf::RenderWindow(sf::VideoMode(2000, 2000),
                                     " Boids behaviors ");
  mp_timer = new Timer();
  mp_fsm = new cFSM();

  m_grid = std::make_unique<enGrid>();

  m_grid->init(30,30,5000.f,5000.f);


  if( !this->createAllBoids() )
    return false;

  mp_fsm->init(m_boids, mp_target);

  for( size_t i = 1; i < 5 + 1; ++i )
  {
    m_nodes.addNode(enPathNode(enVector2(std::cosf(i * gvars::quarterPi) * 1000.0f,
                    1000.0f * sinf(i * gvars::quarterPi))));//quarter
  }


  if( !this->setAllBoids() )
    return false;



  return true;
}

int
AppSteeringBehaviors::run()
{
  while( mp_window->isOpen() )
  {
    mp_window->clear();
    mp_timer->StartTiming();

    this->windowEvents();

    this->m_grid->drawGrid(*mp_window);
    //const float FrameTime = mp_timer->GetResultSecondsFloat();

    //this->mp_fsm->executeMachine(FrameTime);

    //m_boids[i].m_sprite.setPosition(m_boids[i].m_position.X, m_boids[i].m_position.Y);

    //for( Boid& boid : m_boids )
    //{

    //  mp_window->draw(boid.m_sprite);
    //  mp_window->draw(sfHelp::CreateVisualLine(boid.getPosition(),
    //                    boid.getPrevForce(),
    //                    500.0f));
    //}

    //for( size_t i = 0; i < m_nodes.getSize(); i++ )
    //{
    //  enPathNode* ptrToNode = m_nodes.getPtr(i);
    //  mp_window->draw(sfHelp::CreateCircle(ptrToNode->m_position));
    //}

    mp_window->display();

    mp_timer->EndTiming();
  }

  return 0;
}

void
AppSteeringBehaviors::destroy()
{
  if( mp_target != nullptr )
  {
    delete mp_target;
    mp_target = nullptr;
  }

  if( mp_window != nullptr )
  {
    delete  mp_window;
    mp_window = nullptr;
  }

  if( mp_timer != nullptr )
  {
    delete mp_timer;
    mp_timer = nullptr;
  }

  if( mp_fsm != nullptr )
  {
    delete mp_fsm;
    mp_fsm = nullptr;
  }

}

bool
AppSteeringBehaviors::createAllBoids()
{

  for( size_t i = 0; i < s_totalBoids; ++i )
  {
    m_boids.emplace_back();
  }
  return true;
}

bool
AppSteeringBehaviors::setAllBoids()
{
  uint32_t Difference = 0;

  for( Boid& boid : m_boids )
  {
    if( !boid.loadSprite("../resources/sprites/S_generic_boid.png") )
    {
      return false;
    }
    boid.setSpeed(100.0f);
    boid.m_sprite.setColor(sf::Color(100, 100, 100, 255));

    sf::Vector2u sizeOfSprite = boid.m_texture.getSize();

    boid.m_sprite.setOrigin(sizeOfSprite.x / 2,
                            sizeOfSprite.y / 2);

    boid.setPosition(mp_window->getSize().x / 6 + Difference, mp_window->getSize().y / 2);
    sfHelp::Resize(boid.m_sprite, s_minimumWidth * 5u, s_minimumHeight * 5u);
    Difference += s_minimumWidth * 5u * 2;
  }

  return true;
}

void
AppSteeringBehaviors::windowEvents()
{

  sf::Event windowEvent;
  while( mp_window->pollEvent(windowEvent) )
  {
    if( windowEvent.type == sf::Event::Closed )
      mp_window->close();

    if( windowEvent.type == sf::Event::Resized )
    {
      sf::FloatRect const newWindowSize(0,
                                        0,
                                        windowEvent.size.height,
                                        windowEvent.size.width);

      mp_window->setView(sf::View(newWindowSize));
    }

    if( windowEvent.type == sf::Event::MouseButtonPressed )
    {
      sf::Vector2i const MousePosition = sf::Mouse::getPosition(*mp_window);

      sf::Vector2f const worldPosition = mp_window->mapPixelToCoords(MousePosition);

      mp_target->setPosition(worldPosition.x, worldPosition.y);
    }

    if( windowEvent.type == sf::Event::KeyPressed )
    {
      sf::View currentViewPort = mp_window->getView();

      if( windowEvent.key.code == sf::Keyboard::W )
      {
        currentViewPort.move(sf::Vector2f(0.0f, -100.0f));
        mp_window->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::S )
      {
        currentViewPort.move(sf::Vector2f(0.0f, 100.0f));
        mp_window->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::A )
      {
        currentViewPort.move(sf::Vector2f(-100.0f, 0.0f));
        mp_window->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::D )
      {
        currentViewPort.move(sf::Vector2f(100.0f, 0.0f));
        mp_window->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::R )
      {
        enVector2 Position = m_boids[0].m_position;
        sf::Vector2 const sfmlPosition = sfHelp::ConvertToSfmlVector(Position);
        currentViewPort.setCenter(sfmlPosition);
        mp_window->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::LControl )
      {
        mp_window->setView(mp_window->getDefaultView());
      }


    }

  }
}
