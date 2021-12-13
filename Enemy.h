#pragma once
#include "SDLGameObject.h"
#include "Game.h"

class Enemy : public SDLGameObject
{
public:
  Enemy(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
  void random();
  void checkCollision();

private:
	int time = 0;
	bool wait = false;
	int LR = 0; //1 == 왼쪽으로 감, 2 == 오른쪽으로 감
	int speed = -1;
}; 