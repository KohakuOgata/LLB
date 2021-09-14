#pragma once
#include "SceneBase.h"
#include "Define.h"

struct PlayerResult;

class ResultScene :
    public SceneBase
{
public:
	ResultScene(IOnSceneChangedListener* _impl, const Parameter& _parameter);
	~ResultScene();

	void Update() override;
	void Draw() override;

private:

private:
	std::list<PlayerResult> results;
	Define::ETeam winTeam;
	int winTeamFontHandle;
	int mainFontHandle;
};

struct PlayerResult {
	PlayerResult(int _no, int _team, int _hit, int _out) :
		no(_no), team(_team), hit(_hit), out(_out) {}
	int no;
	int team;
	int hit;
	int out;
};