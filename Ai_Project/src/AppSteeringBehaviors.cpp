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
  m_pTarget = new Boid(200, 200);
  m_pWindow = new sf::RenderWindow(sf::VideoMode(2000, 2000),
                                     " Boids behaviors ");
  m_pTimer = new Timer();
  m_pFsm = new cFSM();

  m_pPlayer = std::make_unique<Boid>();

  m_pGrid = std::make_unique<enGrid>();

  m_pRoom = std::make_unique<enRoom>();

  m_pRoom->readFile("../resources/maps/level_1.txt");

  m_pGrid->init(30,30,5000.f,5000.f);


  if( !this->createAllBoids() )
    return false;

  m_pFsm->init(m_boids, m_pTarget);

  for( size_t i = 1; i < 5 + 1; ++i )
  {
    enPathNode node;
    node.m_position.X = std::cosf(i * gvars::quarterPi) * 1000.0f;
    node.m_position.Y = std::sinf(i * gvars::quarterPi) * 1000.0f;
    node.m_radius = 130.f;

    m_nodes.addNode( (node));//quarter
  }


  if( !this->setAllBoids() )
    return false;


  if( !this->setUpPlayer() )
      return false;

  return true;
}

int
AppSteeringBehaviors::run()
{
  while( m_pWindow->isOpen() )
  {
    m_pWindow->clear();
    m_pTimer->StartTiming();

    this->windowEvents();


    for( Boid& boid : m_boids )
    {
      boid.seek(m_pTarget->getPosition(),1.0f);
    }

    m_pRoom->draw(*m_pWindow);

    for( Boid& boid : m_boids )
    {
      m_pWindow->draw(boid.m_sprite);
      m_pWindow->draw(sfHelp::CreateVisualLine(boid.getPosition(),
                        boid.getPrevForce(),
                        100.0f));
    }
    m_pWindow->draw(m_pPlayer->m_sprite);

    m_pWindow->draw(sfHelp::CreateVisualLine(m_pPlayer->getPosition(),
                    m_pPlayer->getPrevForce(),
                    100.0f));

    //for( size_t i = 0; i < m_nodes.getSize(); i++ )
    //{
    //  enPathNode* ptrToNode = m_nodes.getPtr(i);
    //  m_pWindow->draw(sfHelp::CreateCircle(ptrToNode->m_position));
    //}

    m_pTimer->EndTiming();

    update(m_pTimer->GetResultSecondsFloat());
    m_pWindow->display();
  }

  return 0;
}

void
AppSteeringBehaviors::destroy()
{
  if( m_pTarget != nullptr )
  {
    delete m_pTarget;
    m_pTarget = nullptr;
  }

  if( m_pWindow != nullptr )
  {
    delete  m_pWindow;
    m_pWindow = nullptr;
  }

  if( m_pTimer != nullptr )
  {
    delete m_pTimer;
    m_pTimer = nullptr;
  }

  if( m_pFsm != nullptr )
  {
    delete m_pFsm;
    m_pFsm = nullptr;
  }

}

bool 
AppSteeringBehaviors::update(float elapsedTime)
{
  for( Boid& boid : m_boids )
  {
    boid.update(elapsedTime);
  }

  m_pPlayer->update(elapsedTime);

  sf::View currentView = m_pWindow->getView();

  sf::Vector2 const sfmlPosition = sfHelp::ConvertToSfmlVector(m_pPlayer->getPosition());
  currentView.setCenter(sfmlPosition);
  m_pWindow->setView(currentView);

  return true;
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
    boid.m_sprite.setColor(sf::Color(100, 100, 100, 255));

    sf::Vector2u const sizeOfSprite = boid.m_texture.getSize();

    boid.m_sprite.setOrigin(sizeOfSprite.x / 2,
                            sizeOfSprite.y / 2);

    boid.setPosition(m_pWindow->getSize().x / 6 + Difference, m_pWindow->getSize().y / 2);
    sfHelp::Resize(boid.m_sprite, s_minimumWidth * 5u, s_minimumHeight * 5u);
    Difference += s_minimumWidth * 5u * 2;
  }

  return true;
}

bool 
AppSteeringBehaviors::setUpPlayer()
{
  if(!m_pPlayer->loadSprite("../resources/sprites/S_generic_boid.png") )
  {
    return false;
  }
  else
  {
    m_pPlayer->m_sprite.setColor(sf::Color::Red);
    m_pPlayer->setPosition(0.0f, 0.0f);
    m_pPlayer->m_maxForce = 4.0f;
    m_pPlayer->setSpeed(100.0f);

    sf::Vector2u const sizeOfSprite = m_pPlayer->m_texture.getSize();

    m_pPlayer->m_sprite.setOrigin(sizeOfSprite.x * 0.5f,
                                  sizeOfSprite.y * 0.5f);

    sfHelp::Resize(m_pPlayer->m_sprite, s_minimumWidth * 5u, s_minimumHeight * 5u);
  }

  return true;
}

void
AppSteeringBehaviors::windowEvents()
{

  sf::Event windowEvent;
  while( m_pWindow->pollEvent(windowEvent) )
  {
    if( windowEvent.type == sf::Event::Closed )
      m_pWindow->close();

    if( windowEvent.type == sf::Event::Resized )
    {
      sf::FloatRect const newWindowSize(0,
                                        0,
                                        windowEvent.size.height,
                                        windowEvent.size.width);

      m_pWindow->setView(sf::View(newWindowSize));
    }

    if( windowEvent.type == sf::Event::MouseButtonPressed )
    {
      sf::Vector2i const MousePosition = sf::Mouse::getPosition(*m_pWindow);

      sf::Vector2f const worldPosition = m_pWindow->mapPixelToCoords(MousePosition);

      m_pTarget->setPosition(worldPosition.x, worldPosition.y);
    }

    if( windowEvent.type == sf::Event::KeyPressed )
    {
      sf::View currentViewPort = m_pWindow->getView();

      if( windowEvent.key.code == sf::Keyboard::W )
      {
        currentViewPort.move(sf::Vector2f(0.0f, -100.0f));
        m_pWindow->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::S )
      {
        currentViewPort.move(sf::Vector2f(0.0f, 100.0f));
        m_pWindow->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::A )
      {
        currentViewPort.move(sf::Vector2f(-100.0f, 0.0f));
        m_pWindow->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::D )
      {
        currentViewPort.move(sf::Vector2f(100.0f, 0.0f));
        m_pWindow->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::R )
      {
        enVector2 Position = m_boids[0].m_position;
        sf::Vector2 const sfmlPosition = sfHelp::ConvertToSfmlVector(Position);
        currentViewPort.setCenter(sfmlPosition);
        m_pWindow->setView(currentViewPort);
      }
      if( windowEvent.key.code == sf::Keyboard::LControl )
      {
        m_pWindow->setView(m_pWindow->getDefaultView());
      }

      if( windowEvent.key.code == sf::Keyboard::Left )
      {
        m_pPlayer->seek(m_pPlayer->getPosition() + enVector2::westVector, 3.0f);
      }

      if( windowEvent.key.code == sf::Keyboard::Right )
      {
        m_pPlayer->seek(m_pPlayer->getPosition() + enVector2::eastVector, 3.0f);
      }

      if( windowEvent.key.code == sf::Keyboard::Up)
      {
        m_pPlayer->seek(m_pPlayer->getPosition() + enVector2::northVector, 3.0f);
      }

      if( windowEvent.key.code == sf::Keyboard::Down)
      {
        m_pPlayer->seek(m_pPlayer->getPosition() + enVector2::southVector, 3.0f);
      }

    }

  }
}
