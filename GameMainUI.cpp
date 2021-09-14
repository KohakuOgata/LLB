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
const Double2 GameMainUI::HitStopGuageSize = Double2(200, 50);
const int GameMainUI::HitStopGuageX = 600;
const int GameMainUI::StockRadius = 10;

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
	DrawHitStopGuage();
}

void GameMainUI::DrawHealthGuages() const
{
	const int maxStock = GetScene()->FindGameObject<GameManager>()->GetPlayerMaxStock();
	for (const auto& player : GetScene()->FindGameObjects<Player>()) {
		const int i = player->GetPlayerNo();
		const int DrawX = -HealthGuageSize.x / 2 + Config::WindowSize.x / (PlayerNum + 1) * (i + 1);
		const int DrawY = -HealthGuageSize.y / 2 + HealthGuageY;
		DrawBox(DrawX - HealthGuageBorderThickNess, DrawY - HealthGuageBorderThickNess, DrawX + HealthGuageSize.x + HealthGuageBorderThickNess, DrawY + HealthGuageSize.y + HealthGuageBorderThickNess, HealthGuageBorderColor, true);
		DrawBox(DrawX, DrawY, DrawX + HealthGuageSize.x * player->GetLife() / GetScene()->FindGameObject<GameManager>()->GetPlayerMaxLife(), DrawY + HealthGuageSize.y, HealthGuageBodyColor, true);
		for (int i = 0; i < maxStock; i++) {
			DrawCircle(DrawX + StockRadius * 3 * i, DrawY + HealthGuageSize.y + StockRadius * 2, StockRadius, Color::Get(ColorID::Black), (i < player->GetStock()) ? 1 : 0);
		}
	}
}

void GameMainUI::DrawHitStopGuage() const
{
	int factor = 1;
	const double rate = GetScene()->FindGameObject<Ball>()->GetHitStopProgressRate();
	const Double2 windowSize = Config::WindowSize;
	for (int i = 0; i < 2; i++) {
		DrawBox(HitStopGuageX, BallSpeedHeight, HitStopGuageX + HitStopGuageSize.x, BallSpeedHeight + HitStopGuageSize.y, GetColor(255, 128, 0), false);
		DrawBox(HitStopGuageX + HitStopGuageSize.x * (1.0 - rate), BallSpeedHeight, HitStopGuageX + HitStopGuageSize.x, BallSpeedHeight + HitStopGuageSize.y, GetColor(255, 128, 0), true);
		DrawBox(windowSize.x - HitStopGuageX - HitStopGuageSize.x, BallSpeedHeight, windowSize.x - HitStopGuageX, BallSpeedHeight + HitStopGuageSize.y, GetColor(255, 128, 0), false);
		DrawBox(windowSize.x - HitStopGuageX - HitStopGuageSize.x, BallSpeedHeight, windowSize.x - HitStopGuageX - HitStopGuageSize.x + HitStopGuageSize.x * rate, BallSpeedHeight + HitStopGuageSize.y, GetColor(255, 128, 0), true);
	}
}
