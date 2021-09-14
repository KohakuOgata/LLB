#include "ResultScene.h"

#include "Parameter.h"
#include "Utility.h"
#include "Define.h"
#include "Config.h"
#include "Primitive2D.h"
#include "VInput.h"
#include "SceneID.h"

#include <DxLib.h>

ResultScene::ResultScene(IOnSceneChangedListener* _impl, const Parameter& _parameter):
	SceneBase(_impl, _parameter)
{
	for (int i = 0; i < 4; i++) {
		if (_parameter.get(std::to_string(i) + std::string("Team")) == -1)
			break;
		results.push_back(
			PlayerResult(
				i,
				_parameter.get(std::to_string(i) + std::string("Team")),
				_parameter.get(std::to_string(i) + std::string("Hit")),
				_parameter.get(std::to_string(i) + std::string("Out"))));
	}
	int lessOut = 100;
	for (const auto& result : results) {
		if (result.out < lessOut) {
			lessOut = result.out;
			winTeam = result.team - 1;
		}
	}
	winTeamFontHandle = CreateFontToHandle(NULL, 150, -1);
	mainFontHandle = CreateFontToHandle(NULL, 100, -1);
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (VInput::GetIns()->GetPushDown(VButtonID::Escape)) {
		ChangeScene(SceneID::Title, Parameter(), true);
	}
}

void ResultScene::Draw()
{
	unsigned int teamColors[] = {
		Color::Get(ColorID::Red),
		Color::Get(ColorID::Blue),
		Color::Get(ColorID::Yellow),
		Color::Get(ColorID::Green)
	};
	std::string teamString[] = {
		"RED",
		"BLUE",
		"YELLOW",
		"GREEN"
	};

	DrawFormatStringToHandle(Config::WindowCenter.x, 200, teamColors[winTeam], winTeamFontHandle, "%s WIN!", teamString[winTeam].c_str());

}
