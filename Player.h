#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
public:
  Player(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
  void handleInput();
  void checkCollision();
  void sprite();

  bool isGround = false;

  bool Left = true;
  bool Right = true;

  int a_key = 0; //1왼 2오

  int p_time = 0;
};

#endif