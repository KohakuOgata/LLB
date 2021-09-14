#include "PlayerEntryScene.h"
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "Input.h"
#include "SceneID.h"
#include "DebugMode.h"

#include <string>

const double PlayerEntryScene::DefaultInitialBallSpeed = 8.0;

PlayerEntryScene::PlayerEntryScene(IOnSceneChangedListener* _impl, const Parameter& _parameter) :
	SceneBase(_impl, _parameter),
	playerInfo(),
	initialBallSpeed(DefaultInitialBallSpeed)
{
}

PlayerEntryScene::~PlayerEntryScene()
{
}

void PlayerEntryScene::Update()
{
	SceneBase::Update();
	EntryUpdate();
	ExitUpdate();
	if (Input::GetPushDown(InputID::KeyReturn))
		GoGameMainScene();
}

void PlayerEntryScene::Draw()
{
	SceneBase::Draw();
}

void PlayerEntryScene::DebugDraw()
{
	printfDx("PlayerEntryScene\n");
}

void PlayerEntryScene::EntryUpdate()
{
	if (Input::GetPushDown(InputID::KeySpace))
		TryEntryPlayer(Define::EController::Keyboard);
	if (Input::GetPushDown(InputID::Pad1A))
		TryEntryPlayer(Define::EController::Pad1);
	if (Input::GetPushDown(InputID::Pad2A))
		TryEntryPlayer(Define::EController::Pad2);
	if (Input::GetPushDown(InputID::Pad3A))
		TryEntryPlayer(Define::EController::Pad3);
	if (Input::GetPushDown(InputID::Pad4A))
		TryEntryPlayer(Define::EController::Pad4);
}

void PlayerEntryScene::TryEntryPlayer(const Define::EController controller)
{
	for (const auto& it : playerInfo) {
		if (it.controller == controller) {
			GoGameMainScene();
			return;
		}
	}
	playerInfo.push_back(PlayerInfo(controller, static_cast<Define::ETeam>(playerInfo.size() + 1)));
}

void PlayerEntryScene::GoGameMainScene()
{
	if (playerInfo.empty())
		return;
	Parameter param;
	param.set("PlayerMaxStock", 4);
	param.set("PlayerMaxLife", 100);
	param.set("PlayerNum", playerInfo.size());
	param.set("InitialBallSpeed", initialBallSpeed);
	for (int i = 0; i < playerInfo.size(); i++) {
		param.set(std::string("PCon").insert(1, std::to_string(i + 1)).c_str(), static_cast<int>(playerInfo.at(i).controller));
		param.set(std::string("PTeam").insert(1, std::to_string(i + 1)).c_str(), static_cast<int>(playerInfo.at(i).team));
	}
	ChangeScene(SceneID::GameMain, param, false);
	return;
}

void PlayerEntryScene::ExitUpdate()
{
	if (Input::GetPushDown(InputID::KeyEscape))
		TryExitPlayer(Define::EController::Keyboard);
	if (Input::GetPushDown(InputID::Pad1B))
		TryExitPlayer(Define::EController::Pad1);
	if (Input::GetPushDown(InputID::Pad2B))
		TryExitPlayer(Define::EController::Pad2);
	if (Input::GetPushDown(InputID::Pad3B))
		TryExitPlayer(Define::EController::Pad3);
	if (Input::GetPushDown(InputID::Pad4B))
		TryExitPlayer(Define::EController::Pad4);
}

void PlayerEntryScene::TryExitPlayer(const Define::EController controller)
{
	for (auto it = playerInfo.begin(); it != playerInfo.end(); it++) {
		if (it->controller == controller) {
			playerInfo.erase(it);
			return;
		}
	}
	ChangeScene(SceneID::Title, Parameter(), true);
}

PlayerEntryScene::PlayerInfo::PlayerInfo(const Define::EController _controller, const Define::ETeam _team):
	controller(_controller),
	team(_team)
{
}

PlayerEntryScene::PlayerInfo::~PlayerInfo()
{
}
