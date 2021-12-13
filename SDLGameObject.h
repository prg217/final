#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include <iostream>
#include <random>

class SDLGameObject : public GameObject
{
public:
    bool active = true;
    int HP = 10;
    bool isHit = false;

  SDLGameObject(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean() { }
  virtual Vector2D GetPos() { return m_position; }
  virtual int GetWidth() { return m_width; }
  virtual ~SDLGameObject() {}
  SDL_Rect& getD_rect()
  {
    return d_rect;
  }
  bool check_collision(SDL_Rect& rect);

protected:
  int m_width;
  int m_height;
  int m_currentRow;
  int m_currentFrame;
  std::string m_textureID;

  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Rect d_rect;

  int c_key = 0;
};

#endif