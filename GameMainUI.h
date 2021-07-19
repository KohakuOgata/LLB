#pragma once
#include "UI.h"
class GameMainUI :
	public UI
{
public:
	GameMainUI(SceneBase* _scene);
	~GameMainUI();

	void Draw() override;

private:
	static const int BallSpeedHeight;
	int BallSpeedFont;
};

