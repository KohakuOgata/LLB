#pragma once

#include "SceneBase.h"
#include "Define.h"

#include <memory>

class IOnSceneChangedListener;
class Parameter;
class Stage;

class GameMainScene : public SceneBase {
public:
	GameMainScene(IOnSceneChangedListener* _impl, const Parameter& _parameter);
	~GameMainScene();

	void Update() override;
	void Draw() override;
	void DebugDraw() override;

private:
	void Init();
	void GameSet();
	
private:

};