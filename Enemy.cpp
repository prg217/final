#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams)
	: SDLGameObject(pParams)
{

}

void Enemy::draw()
{
	if (active)
	{
		SDLGameObject::draw();
		wait = false;
	}
}

void Enemy::update()
{
	if (!active && !wait) //죽었다면
	{
		time = SDL_GetTicks();
		wait = true; //time이 계속 저장되는거 방지용
	}

	if (!active && (SDL_GetTicks() >= (time + 5000))) //죽은 뒤 5초 후 재소환 할 수 있게
	{
		if (LR == 1)
		{
			m_position.setX(704);
			flip = SDL_FLIP_NONE;
			speed = -1;
		}
		else if (LR == 2)
		{
			m_position.setX(-64);
			flip = SDL_FLIP_HORIZONTAL;
			speed = 1;
		}


		//시간 지연해주고 random불러오기
		random();
	}

	m_velocity.setX(speed);

	if (m_position.getX() > 710 || m_position.getX() < -75) //밖으로 나가면
	{
		active = false;
	}

	if (active) //살아 있을 때만
	{
		checkCollision();
	}

	SDLGameObject::update();
}

void Enemy::random()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> appear(0.0f, 100.0f); //등장확률
	std::uniform_int_distribution<int> LorR(0, 1); //왼쪽으로 갈것인가 오른쪽으로 갈것인가
	std::uniform_int_distribution<int> Y(0, 400); //Y축

	if (appear(gen) > 99)
	{
		active = true;
	}

	if (LorR(gen) == 0)
	{
		LR = 1; //왼쪽으로
	}
	else
	{
		LR = 2; //오른쪽으로
	}

		m_position.setY(Y(gen));
}

void Enemy::checkCollision()
{
	if (TheGame::Instance()->m_gameObjects["player"] != 0) //플레이어와 충돌했을때
	{
		if (SDLGameObject::check_collision(TheGame::Instance()->m_gameObjects["player"]->getD_rect()))
		{
      m_position.setY(-64);
			active = false;
			time = 0;

			TheGame::Instance()->m_gameObjects["player"]->HP -= 1;
			TheGame::Instance()->m_gameObjects["player"]->isHit = true;
			TheAudioManager::Instance()->playEffect(Effect::s_hit);
		}
	}
}

void Enemy::clean()
{
}