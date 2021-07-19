#include "TitleScene.h"

#include "Input.h"
#include "Parameter.h"
#include "IOnSceneChangedListener.h"
#include "SceneID.h"
#include "VInput.h"
#include "DebugMode.h"

#include <DxLib.h>

namespace {

}

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter)
	: SceneBase(impl, parameter)
{
}

void TitleScene::Update()
{
	if (VInput::GetIns()->GetPushDown(VButtonID::Enter)) {
		ChangeScene(SceneID::PlayerEntry, Parameter(), true);
	}
}

void TitleScene::Draw()
{
}

bool TitleScene::Terminate()
{
	return Input::GetPushDown(InputID::KeyEscape);
}

void TitleScene::DebugDraw()
{
	printfDx("Title Scene\n\n");

	printfDx("\n");
}
