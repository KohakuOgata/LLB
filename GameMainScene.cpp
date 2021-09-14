#include "GameMainScene.h"

#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "Input.h"
#include "SceneID.h"
#include "Config.h"
#include "Primitive2D.h"
#include "VInput.h"
#include "Define.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Ball.h"
#include "GameMainUI.h"

#include <DxLib.h>
#include <string>

GameMainScene::GameMainScene(IOnSceneChangedListener* _impl, const Parameter& _parameter): 
	SceneBase(_impl, _parameter)
{
	CreateGameObject<Stage>();
	CreateGameObject<Camera>();
	CreateGameObject<GameManager>();
	FindGameObject<GameManager>()->Set(_parameter.get("PlayerMaxStock"), _parameter.get("PlayerMaxLife"));
	for (int i = 1; i <= _parameter.get("PlayerNum"); i++) {
		Player& player = *CreateGameObject<Player>();
		player.SetController((Define::EController)_parameter.get(std::string("PCon").insert(1, std::to_string(i)).c_str()));
		player.SetTeam((Define::ETeam)_parameter.get(std::string("PTeam").insert(1, std::to_string(i)).c_str()));
	}

	CreateGameObject<Ball>();
	FindGameObject<Ball>()->SetInitialSpeed(_parameter.get("InitialBallSpeed"));
	CreateGameObject<GameMainUI>();
	
	Init();
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Update()
{
	SceneBase::Update();
	if (VInput::GetIns()->GetPushDown(VButtonID::Escape)) {
		Parameter parameter;
		ChangeScene(SceneID::Title, parameter, true);
	}
	if (FindGameObject<GameManager>()->GetIsGameSetted()) {
		GameSet();
	}
}

void GameMainScene::Draw() 
{
	SceneBase::Draw();
	printfDx("GameMainScene\n\n");
}

void GameMainScene::Init()
{
	
}

void GameMainScene::GameSet()
{
	Parameter param;
	int i = 0;
	for (const auto& player : FindGameObjects<Player>()) {
		param.set(std::to_string(i) + std::string("Team"), player->GetTeam());
		param.set(std::to_string(i) + std::string("Hit"), player->GetHit());
		param.set(std::to_string(i) + std::string("Out"), player->GetOut());
		i++;
	}
	for (; i < 4; i++) {
		param.set(std::to_string(i) + std::string("Team"), -1);
	}
	param.set("WinTeam", FindGameObject<GameManager>()->GetWinTeam());
	ChangeScene(SceneID::Result, param, true);
}

void GameMainScene::DebugDraw()
{
	printfDx("GameMainScene\n");

	printfDx("\n");
	SceneBase::DebugDraw();
}