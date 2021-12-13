#ifndef __Game__
#define __Game__

#include <iostream>
#include <vector>
#include <map>
#include "SDL.h"
#include "TextureManager.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "SDL_ttf.h"
#include <sstream>
//#include "SDL_mixer.h"
#include "AudioManager.h"

class Game
{
public:
  static Game* Instance()
  {
    if (s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }
    return s_pInstance;
  }
  SDL_Renderer* getRenderer() const { return m_pRenderer; }

  bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
  void render();
  void update();
  bool running();
  void handleEvents();
  void clean();
  void quit() { m_bRunning = false; }
  template <class T>
  void create(T* t)
  {
    m_gameObjects["z_attack"] = t; //공격 물체 소환
  }
  template <class T>
  void create2(T* t)
  {
#ifdef WIN32
    Mix_PauseMusic();
#endif
    m_gameObjects["z_gameOver"] = t; //게임오버
  }
  void PaintText(const char* str, int x, int y);

private:
  Game() {}
  ~Game() {}
  static Game* s_pInstance;
  int error_check = 0; //error_check값을 0으로 한 후 성공할때마다 1씩 더해줌! 그리고 다 통과되지 않으면 그 값이 그렇게 될 수 없으니 만약 몇 이하면 false로 만들어준다. 

  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  bool m_bRunning;

  bool die = false; //플레이어가 죽는지 체크
  int time = 0;

public:
  std::map<std::string, SDLGameObject*> m_gameObjects;
  //std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif /*defined(__Game__)*/