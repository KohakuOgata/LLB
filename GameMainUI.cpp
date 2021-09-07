#include "GameMainUI.h"

#include "Config.h"
#include "Primitive2D.h"
#include "Ball.h"
#include "SceneBase.h"
#include "Player.h"
#include "Color.h"
#include "GameManager.h"

#include <DxLib.h>

const int GameMainUI::BallSpeedHeight = 900;
const Double2 GameMainUI::HealthGuageSize = Double2(200, 20);
const int GameMainUI::HealthGuageBorderThickNess = 5;
const int GameMainUI::HealthGuageY = 200;

GameMainUI::GameMainUI(SceneBase* _scene):
	UI(_scene),
	BallSpeedFont(-1),
	PlayerNum(Player::GetPlayerNum()),
	HealthGuageBodyColor(Color::Get(ColorID::Yellow)),
	HealthGuageBorderColor(Color::Get(ColorID::Black))
{
	BallSpeedFont = CreateFontToHandle(NULL, 100, -1, -1);
}

GameMainUI::~GameMainUI()
{
	DeleteFontToHandle(BallSpeedFont);
	BallSpeedFont = -1;
}

void GameMainUI::Draw()
{
	DrawFormatStringToHandle(screen->Width() / 2, BallSpeedHeight, Color::Get(ColorID::Black), BallSpeedFont, "%d", GetScene()->FindGameObject<Ball>()->GetSpeed());
	DrawHealthGuages();
}

void GameMainUI::DrawHealthGuages() const
{
	auto Players = GetScene()->FindGameObjects<Player>();

	for (const auto& player : Players) {
		const int i = player->GetPlayerNo();
		const int DrawX = -HealthGuageSize.x / 2 + Config::WindowSize.x / (PlayerNum + 1) * (i + 1);
		const int DrawY = -HealthGuageSize.y / 2 + HealthGuageY;
		DrawBox(DrawX - HealthGuageBorderThickNess, DrawY - HealthGuageBorderThickNess, DrawX + HealthGuageSize.x + HealthGuageBorderThickNess, DrawY + HealthGuageSize.y + HealthGuageBorderThickNess, HealthGuageBorderColor, true);
		DrawBox(DrawX, DrawY, DrawX + HealthGuageSize.x * player->GetLife() / GetScene()->FindGameObject<GameManager>()->GetPlayerMaxLife(), DrawY + HealthGuageSize.y, HealthGuageBodyColor, true);
	}
}
