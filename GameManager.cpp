#include "GameManager.h"

#include "SceneBase.h"
#include "Player.h"
#include "Define.h"
#include "Ball.h"

const double GameManager::HitStop = 1.0;

GameManager::GameManager(SceneBase* _pScene):
	GameObject(_pScene), 
	round(0), 
	isGameSetted(false)
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

void GameManager::PlayerDied(const Player& DiedPlayer)
{
	std::list<Define::ETeam> aliveTeams;
	for (const auto& player : GetScene()->FindGameObjects<Player>()) {
		if (player->GetIsAlive()) {
			bool isExist = false;
			for (auto& aliveTeam : aliveTeams) {
				if (aliveTeam == player->GetTeam()) {
					isExist = true;
					break;
				}
			}
			if (!isExist)
				aliveTeams.push_back(player->GetTeam());
		}
	}
	if (aliveTeams.size() <= 1) {
		std::list<Define::ETeam> haveStockTeams;
		for (const auto& player : GetScene()->FindGameObjects<Player>()) {
			if (player->GetStock()) {
				bool isExist = false;
				for (auto& team : haveStockTeams) {
					if (team == player->GetTeam()) {
						isExist = true;
						break;
					}
				}
				if (!isExist)
					haveStockTeams.push_back(player->GetTeam());
			}
		}
		if (haveStockTeams.size() <= 1) {
			winTeam = haveStockTeams.front();
			GameSet();
		}
		else
			RoundStart();
	}
}

bool GameManager::GetIsGameSetted() const
{
	return isGameSetted;
}

int GameManager::GetWinTeam() const
{
	return winTeam;
}

void GameManager::RoundStart()
{
	GetScene()->FindGameObject<Ball>()->Start();
	for (auto& player : GetScene()->FindGameObjects<Player>())
		player->Start();
}

void GameManager::GameSet()
{
	isGameSetted = true;
}
