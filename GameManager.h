#pragma once
#include "GameObject.h"
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

private:
	int playerMaxStock;
	int playerMaxLife;
	int playerMaxSpecial;
	int round;

};

