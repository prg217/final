#include "Attack.h"

bool LorR = true; //true 왼 false 오

Attack::Attack(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Attack::draw()
{
  if (setActive == true)
  {
    SDLGameObject::draw();
  }
}

void Attack::update()
{
  handleInput();

  if (m_position.getX() <= 0 || m_position.getX() >= 640)
  {
    attack = false;
    setActive = false;
  }

  if (setActive) //활성화 될때만 체크 표시되게
  {
      checkCollision(); 
  }

  SDLGameObject::update();
}

void Attack::handleInput()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    LorR = false;
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    LorR = true;
  }

  if (LorR == true && attack == false)
  {
    attack = true;
    m_velocity.setX(-2);
  }
  if (LorR == false && attack == false)
  {
    attack = true;
    m_velocity.setX(2);
  }
}

void Attack::checkCollision()
{
  if (TheGame::Instance()->m_gameObjects["enemy"] != 0 && TheGame::Instance()->m_gameObjects["enemy"]->active == true)
  {
    if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["enemy"]->getD_rect()))
    {
      setActive = false;
      TheAudioManager::Instance()->playEffect(Effect::s_hit);
      TheGame::Instance()->m_gameObjects["enemy"]->active = false;
    }
  }
  if (TheGame::Instance()->m_gameObjects["enemy1"] != 0 && TheGame::Instance()->m_gameObjects["enemy1"]->active == true)
  {
      if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["enemy1"]->getD_rect()))
      {
          setActive = false;
          TheAudioManager::Instance()->playEffect(Effect::s_hit);
          TheGame::Instance()->m_gameObjects["enemy1"]->active = false;
      }
  }
  if (TheGame::Instance()->m_gameObjects["enemy2"] != 0 && TheGame::Instance()->m_gameObjects["enemy2"]->active == true)
  {
      if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["enemy2"]->getD_rect()))
      {
          setActive = false;
          TheAudioManager::Instance()->playEffect(Effect::s_hit);
          TheGame::Instance()->m_gameObjects["enemy2"]->active = false;
      }
  }
  if (TheGame::Instance()->m_gameObjects["enemy3"] != 0 && TheGame::Instance()->m_gameObjects["enemy3"]->active == true)
  {
      if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["enemy3"]->getD_rect()))
      {
          setActive = false;
          TheAudioManager::Instance()->playEffect(Effect::s_hit);
          TheGame::Instance()->m_gameObjects["enemy3"]->active = false;
      }
  }
  if (TheGame::Instance()->m_gameObjects["enemy4"] != 0 && TheGame::Instance()->m_gameObjects["enemy4"]->active == true)
  {
      if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["enemy4"]->getD_rect()))
      {
          setActive = false;
          TheAudioManager::Instance()->playEffect(Effect::s_hit);
          TheGame::Instance()->m_gameObjects["enemy4"]->active = false;
      }
  }
}

void Attack::clean()
{
  
}