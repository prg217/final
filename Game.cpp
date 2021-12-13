#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "Background.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
    error_check++;
    
    if (m_pWindow != 0)
    {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      error_check++;

      if (m_pRenderer != 0)
      {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 100, 100, 255);
        error_check++;
      }
    }
  }
  if (TTF_Init() < 0) 
  { 
    printf("Could not initialize font! (%s)\n", TTF_GetError()); 
    return false;
  }
  
  if (error_check < 3)
  {
    return false; //실패
  }

  TheAudioManager::Instance()->playBGM(); //배경음악

  if (!TheTextureManager::Instance()->load("Assets/background.png", "back", m_pRenderer))
  {
    return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/tokeng.png", "player", m_pRenderer))
  {
    return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/block.png", "block", m_pRenderer))
  {
    return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/ghost.png", "enemy", m_pRenderer))
  {
    return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/attack.png", "attack", m_pRenderer))
  {
    return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/vine.png", "vine", m_pRenderer))
  {
      return false;
  }
  if (!TheTextureManager::Instance()->load("Assets/gameOver.png", "gameOver", m_pRenderer))
  {
      return false;
  }

  m_gameObjects["back"] = (new Background(new LoaderParams(0, 0, 640, 480, "back")));

  m_gameObjects["block"] = (new Block(new LoaderParams(440, 416, 128, 64, "block"))); //구름
  m_gameObjects["block1"] = (new Block(new LoaderParams(440, 352, 128, 64, "block")));
  m_gameObjects["block2"] = (new Block(new LoaderParams(150, 100, 128, 64, "block")));
  m_gameObjects["block3"] = (new Block(new LoaderParams(228, 310, 128, 64, "block")));

  m_gameObjects["vine"] = (new Block(new LoaderParams(70, 230, 64, 64, "vine"))); //덩굴
  m_gameObjects["vine1"] = (new Block(new LoaderParams(70, 166, 64, 64, "vine")));
  m_gameObjects["vine2"] = (new Block(new LoaderParams(400, 80, 64, 64, "vine")));
  m_gameObjects["vine3"] = (new Block(new LoaderParams(464, 80, 64, 64, "vine")));

  m_gameObjects["enemy"] = (new Enemy(new LoaderParams(-64, 400, 64, 64, "enemy")));
  m_gameObjects["enemy1"] = (new Enemy(new LoaderParams(-71, 300, 64, 64, "enemy")));
  m_gameObjects["enemy2"] = (new Enemy(new LoaderParams(-70, 200, 64, 64, "enemy")));
  m_gameObjects["enemy3"] = (new Enemy(new LoaderParams(-66, 100, 64, 64, "enemy")));
  m_gameObjects["enemy4"] = (new Enemy(new LoaderParams(-68, 0, 64, 64, "enemy")));

  m_gameObjects["player"] = (new Player(new LoaderParams(300, 416, 64, 64, "player")));

  m_bRunning = true;

  return true;
}

void Game::update()
{
  /*for (int i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->update();
  }*/
  
  //https://www.delftstack.com/ko/howto/cpp/how-to-iterate-over-map-in-cpp/
  for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
  {
    iter->second->update();
  }

  if (m_gameObjects["player"]->HP <= 0)
  {
      die = true;
  }
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  /*for (int i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }*/

  for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
  {
    iter->second->draw();
  }

  if (!die) //죽지 않았을 때
  {
      PaintText("HP : ", 10, 0);
      std::stringstream str1;
      str1 << m_gameObjects["player"]->HP; //플레이어의 HP를 불러오면서 문자로 변환
      PaintText(str1.str().c_str(), 80, 0); //char*로 바꿔서 넣어줌
  }

  if (die) //죽었을 때
  {
      if (time == 0) //한 번만 시간 저장하게 만들어줌
      {
          time = (int)(SDL_GetTicks() / 1000); //초 단위로 끊기
      }
      PaintText("Time : ", 220, 320);
      std::stringstream str2;
      str2 << time; //문자로 변환
      PaintText(str2.str().c_str(), 350, 320); //char*로 바꿔서 넣어줌
  }

  SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

//https://infoarts.tistory.com/59
//https://chp747.tistory.com/361
void Game::PaintText(const char* str, int x, int y)
{
  TTF_Font* font = TTF_OpenFont("Assets/HeirofLightBold.ttf", 32); //폰트와 크기 지정
  SDL_Color color = { 255, 255, 255 }; //글자 색
  SDL_Surface * surface = TTF_RenderText_Solid(font, str, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
  int W = 0, H = 0;
  SDL_QueryTexture(texture, NULL, NULL, &W, &H);
  SDL_Rect dstrect = { x, y, W, H };
  SDL_RenderCopy(m_pRenderer, texture, NULL, &dstrect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  TheInputHandler::Instance()->clean();
  SDL_Quit();
}