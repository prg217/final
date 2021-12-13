#pragma once
#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;
  virtual Vector2D GetPos() = 0;
  virtual int GetWidth() = 0; 
  virtual ~GameObject() {}

protected:
  GameObject(const LoaderParams* pParams) {}
};