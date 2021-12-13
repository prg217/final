#ifndef __Attack__
#define __Attack__

#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"

class Attack : public SDLGameObject
{
public:
  Attack(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
  void handleInput();
  void checkCollision();

  bool attack = false;
  bool setActive = true;
};

#endif