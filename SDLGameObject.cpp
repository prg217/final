#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0,0)
{
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_currentRow = 0;
  m_currentFrame = 0;
}

void SDLGameObject::update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;
}

void SDLGameObject::draw()
{
  TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, d_rect, TheGame::Instance()->getRenderer(), flip);
}

//http://lazyfoo.net/SDL_tutorials/lesson17/index.php
bool SDLGameObject::check_collision(SDL_Rect& rect)
{
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = d_rect.x;
  rightA = d_rect.x + d_rect.w;
  topA = d_rect.y;
  bottomA = d_rect.y + d_rect.h;
      
  //Calculate the sides of rect B
  leftB = rect.x;
  rightB = rect.x + rect.w;
  topB = rect.y;
  bottomB = rect.y + rect.h;

  //If any of the sides from A are outside of B
  if (bottomA <= topB)
  {
      c_key = 1;
      return false;
  }

  if (topA >= bottomB)
  {
      c_key = 2;
      return false;
  }

  if (rightA == leftB)
  {
      c_key = 3;
      return true;
  }
  else if (leftA == rightB)
  {
      c_key = 4;
      return true;
  }

  if (rightA <= leftB)
  {
      //LorR = false;
      c_key = 3;
      return false;
  }

  if (leftA >= rightB)
  {
      //LorR = false;
      c_key = 4;
      return false;
  }

  return true;
}