#include "GameMainUI.h"

#include "Config.h"
#include "Primitive2D.h"
#include "Ball.h"
#include "SceneBase.h"

#include <DxLib.h>

const int GameMainUI::BallSpeedHeight = 900;

GameMainUI::GameMainUI(SceneBase* _scene):
	UI(_scene),
	BallSpeedFont(-1)
{
	BallSpeedFont = CreateFontToHandle(NULL, 64, -1, -1);
}

GameMainUI::~GameMainUI()
{
	DeleteFontToHandle(BallSpeedFont);
	BallSpeedFont = -1;
}

void GameMainUI::Draw()
{
	DrawFormatString(screen->Width() / 2, BallSpeedHeight, Color::Get(ColorID::Black), "%d", GetScene()->FindGameObject<Ball>()->GetSpeed());
}
