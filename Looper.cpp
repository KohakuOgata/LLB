#include "Looper.h"

#include "Parameter.h"
#include "Input.h"
#include "DebugMode.h"
#include "SceneID.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "ResultScene.h"
#include "TestScene.h"
#include "PlayerEntryScene.h"

void TimersUpdate();
void PhysicsesUpdate();
void InputUpdate();
void VInputUpdate();
void TimeUpdate();

namespace {

}

Looper::Looper()
{
	Parameter parameter;
	sceneStack.push(std::make_unique<TitleScene>(this, parameter));
}

Looper::~Looper()
{
}

bool Looper::Loop()
{
	if (Input::GetMultiplePushDown({ InputID::KeyS, InputID::KeyR }))
		const char* im = "stopping";
	TimersUpdate();
	PhysicsesUpdate();
	InputUpdate();
	VInputUpdate();
	TimeUpdate();
	fps.Wait();
	sceneStack.top()->ChangeSceneUpdate();
	sceneStack.top()->PopSceneUpdate();
	sceneStack.top()->Update();
	sceneStack.top()->Draw();
	if (Input::GetMultiplePushDown({ InputID::KeyS, InputID::KeyD, InputID::KeyM })) {
		DebugMode::SwitchDebugMode();
	}
	if (DebugMode::IsDebugMode()) {
		fps.Draw();
		sceneStack.top()->DebugDraw();
		if (Input::GetMultiplePushDown({ InputID::KeyG, InputID::KeyT }))
			sceneStack.top()->GoTestScene();
		DebugMode::Update();
		DebugMode::Draw();
	}
	return !sceneStack.top()->Terminate();
}

void Looper::OnSceneChanged(const SceneID scene, const Parameter parameter, const bool stackClear)
{
	if (stackClear)
		while (!sceneStack.empty())
			sceneStack.pop();
	switch (scene)
	{
	case SceneID::Title:
		sceneStack.push(std::make_unique<TitleScene>(this, parameter));
		break;
	case SceneID::PlayerEntry:
		sceneStack.push(std::make_unique<PlayerEntryScene>(this, parameter));
		break;
	case SceneID::GameMain:
		sceneStack.push(std::make_unique<GameMainScene>(this, parameter));
		break;
	case SceneID::Result:
		sceneStack.push(std::make_unique<ResultScene>(this, parameter));
		break;
	case SceneID::Test:
		sceneStack.push(std::make_unique<TestScene>(this, parameter));
		break;
	default:

		break;
	}
}

void Looper::OnScenePop()
{
	sceneStack.pop();
}