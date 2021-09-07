#include "GameManager.h"

const double GameManager::HitStop = 1.0;

GameManager::GameManager(SceneBase* _pScene):
	GameObject(_pScene), round(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::Set(const int _PlayerMaxStock, const int _PlayerMaxLife)
{
	playerMaxStock = _PlayerMaxStock;
	playerMaxLife = _PlayerMaxLife;
}

int GameManager::GetPlayerMaxStock() const
{
	return playerMaxStock;
}

int GameManager::GetPlayerMaxLife() const
{
	return playerMaxLife;
}

int GameManager::GetPlayerMaxSpecial() const
{
	return playerMaxLife;
}

int GameManager::GetRound() const
{
	return round;
}
