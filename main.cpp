//https://drive.google.com/file/d/1KgmkxL71kvtvztWBf74S-s3eTv1g0qY6/view?usp=sharing

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
  if (TheGame::Instance()->init("rabbit&ghost", 100, 100, 640, 480, false))
  {
    Uint32 frameStart, frameTime;
    while (TheGame::Instance()->running())
    {
      frameStart = SDL_GetTicks();
      TheGame::Instance()->handleEvents();
      TheGame::Instance()->update();
      TheGame::Instance()->render();
      frameTime = SDL_GetTicks() - frameStart;
      if (frameTime < DELAY_TIME)
      {
        SDL_Delay((int)(DELAY_TIME - frameTime));
      }
    }
  }
  else
  {
    std::cout << "game init failure " << SDL_GetError() << "\n";
  }
  TheInputHandler::Instance()->clean();
  TheGame::Instance()->clean();

  return 0;
}
