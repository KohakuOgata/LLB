#pragma once
#include "GameObject.h"

class Player;

class GameManager :
	public GameObject
{
public:
	GameManager(SceneBase* _pScene);
	~GameManager();

	void Set(const int _PlayerMaxStock, const int _PlayerMaxLife);

	int GetPlayerMaxStock() const;
	int GetPlayerMaxLife() const;
	int GetPlayerMaxSpecial() const;
	int GetRound() const;
	void PlayerDied(const Player& DiedPlayer);
	bool GetIsGameSetted() const;
	int GetWinTeam() const;

private:
	void RoundStart();
	void GameSet();

public:
	static const double HitStop;

private:
	int playerMaxStock;
	int playerMaxLife;
	int playerMaxSpecial;
	int round;
	bool isGameSetted;
	int winTeam;
};

