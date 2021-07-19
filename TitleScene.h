#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase {
public:
	TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	~TitleScene() = default;

	void Update() override;
	void Draw() override;

	bool Terminate() override;

private:
	void DebugDraw();
private:
};