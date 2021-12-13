#pragma once
#include "SDLGameObject.h"

class Block : public SDLGameObject
{
public:
  Block(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
};