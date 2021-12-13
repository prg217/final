#include "Player.h"
#include "Attack.h"
#include "GameOver.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
    if (active)
    {
        SDLGameObject::draw();
    }
}

void Player::update()
{
  checkCollision();
  handleInput();
  sprite();
  SDLGameObject::update();

  if (m_position.getY() > 400)
  { //바닥에 닿으면 높이 정지 후 땅으로 인식
    m_velocity.setY(0);
    m_acceleration.setY(0);
    isGround  = true;
  }
  else
  {
    m_acceleration.setY(0.2);
    isGround = false;
  }

  if (m_position.getX() < 0) //외곽으로 못나가게
  {
      Left = false;
  }
  else if (m_position.getX() > 576)
  {
      Right = false;
  }
}

void Player::handleInput()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && Right == true)
  {
    Left = true;
    a_key = 2;
    flip = SDL_FLIP_HORIZONTAL;
    m_velocity.setX(2);
  }
  else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && Left == true)
  {
    Right = true;
    a_key = 1;
    flip = SDL_FLIP_NONE;
    m_velocity.setX(-2);
  }
  else
  {
    m_velocity.setX(0);
  }

  if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) && isGround == true)
  {
    Left = true;
    Right = true;
    m_velocity.setY(-10);
  }
  else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) && !isGround) //바닥에 빨리 떨어짐
  {
      m_acceleration.setY(0.5);
  }

  if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) //총알 발사
  {
    Attack* attack = (new Attack(new LoaderParams(m_position.getX(), m_position.getY() + 10, 16, 16, "attack")));
    TheGame::Instance()->create(attack);
    TheAudioManager::Instance()->playEffect(Effect::s_attack);
  }
}

void Player::sprite()
{
    if (isHit) //맞았을 때
    {
        if (p_time == 0)
        {
            p_time = SDL_GetTicks();
        }

        m_currentRow = 1;
        m_currentFrame = 0;

        if (SDL_GetTicks() >= p_time + 800)
        {
            isHit = false;
            p_time = 0;
        }
    }
    else if (HP <= 0) //죽었을 때
    {
        if (p_time == 0)
        {
            p_time = SDL_GetTicks();
        }

        m_currentRow = 1;
        m_currentFrame = 1;

        if (SDL_GetTicks() >= p_time + 800)
        {
            active = false;
            //그리고 게임 오버창 뜨게 만들어야함
            GameOver* gameOver = (new GameOver(new LoaderParams(0, 0, 640, 480, "gameOver")));
            TheGame::Instance()->create2(gameOver);
        }
    }
    else
    {
        m_currentRow = 0;
        m_currentFrame = ((SDL_GetTicks() / 100) % 3);
    }
}

void Player::checkCollision()
{
    if (TheGame::Instance()->m_gameObjects["block"] != 0) //구름
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["block"]->getD_rect()))
        {
            if (c_key == 1) //위
            {
                m_velocity.setY(0);
                m_acceleration.setY(0);
                Right = true;
                Left = true;

                isGround = true;
            }
            else if (c_key == 3) //왼
            {
                m_velocity.setX(0);
                Right = false;
            }
            else if (c_key == 4) //오
            {
                m_velocity.setX(0);
                Left = false;
            }
            //구름 바로 밑에서 위 판정이 되는 이유는 왼쪽 위 꼭짓점을 기준으로 충돌을 판단해서라고 생각함. 그렇기 때문에 딱 구름의 아래랑 플레이어의 위가 닿아버리면 올라서게 판단이...
            //구름 스프라이트를 반반으로 나눠서 위에쪽만 충돌하게 만들면?
            //옆 충돌은 밑에 쪽이 담당하게 하고...
        }
    }
    if (TheGame::Instance()->m_gameObjects["block1"] != 0)
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["block1"]->getD_rect()))
        {
            if (c_key == 1) //위
            {
                m_velocity.setY(0);
                m_acceleration.setY(0);
                Right = true;
                Left = true;

                isGround = true;
            }
            else if (c_key == 3) //왼
            {
                m_velocity.setX(0);
                Right = false;
            }
            else if (c_key == 4) //오
            {
                m_velocity.setX(0);
                Left = false;
            }
        }
    }
    if (TheGame::Instance()->m_gameObjects["block2"] != 0)
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["block2"]->getD_rect()))
        {
            if (c_key == 1)
            {
                m_velocity.setY(0);
                m_acceleration.setY(0);
                Right = true;
                Left = true;

                isGround = true;
            }
            else if (c_key == 3) //왼
            {
                m_velocity.setX(0);
                Right = false;
            }
            else if (c_key == 4) //오
            {
                m_velocity.setX(0);
                Left = false;
            }
        }
    }
    if (TheGame::Instance()->m_gameObjects["block3"] != 0)
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["block3"]->getD_rect()))
        {
            if (c_key == 2)
            {
                m_velocity.setY(0);
                m_acceleration.setY(0);
                Right = true;
                Left = true;

                isGround = true;
            }
            else if (c_key == 3) //왼
            {
                m_velocity.setX(0);
                Right = false;
            }
            else if (c_key == 4) //오
            {
                m_velocity.setX(0);
                Left = false;
            }
        }
    }

    if (TheGame::Instance()->m_gameObjects["vine"] != 0) //덩굴
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["vine"]->getD_rect()))
        {
            if (c_key == 1) 
            {
                m_velocity.setY(0);
                m_acceleration.setY(0.2);
                isGround = true;
            }
        }
    }
    if (TheGame::Instance()->m_gameObjects["vine1"] != 0) 
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["vine1"]->getD_rect()))
        {
            if (c_key == 1) 
            {
                m_velocity.setY(0);
                m_acceleration.setY(0.2);
                isGround = true;
            }
        }
    }
    if (TheGame::Instance()->m_gameObjects["vine2"] != 0) 
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["vine2"]->getD_rect()))
        {
            if (c_key == 1) 
            {
                m_velocity.setY(0);
                m_acceleration.setY(0.2);
                isGround = true;
            }
        }
    }
    if (TheGame::Instance()->m_gameObjects["vine3"] != 0) 
    {
        if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["vine3"]->getD_rect()))
        {
            if (c_key == 1) 
            {
                m_velocity.setY(0);
                m_acceleration.setY(0.2);
                isGround = true;
            }
        }
    }
}

void Player::clean() {}