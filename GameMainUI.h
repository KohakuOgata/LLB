#pragma once
#include "UI.h"

class Double2;


class GameMainUI :
	public UI
{
public:
	GameMainUI(SceneBase* _scene);
	~GameMainUI();

	void Draw() override;

	void DrawHealthGuages() const;
private:
	static const int BallSpeedHeight;
	int BallSpeedFont;
	const int PlayerNum;
	const unsigned int HealthGuageBodyColor;
	const unsigned int HealthGuageBorderColor;

	static const Double2 HealthGuageSize;
	static const int HealthGuageBorderThickNess;
	static const int HealthGuageY;
};

