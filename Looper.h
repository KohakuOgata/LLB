#pragma once

#include "IOnSceneChangedListener.h"
#include "Fps.h"

#include <stack>
#include <memory>

class SceneBase;

class Looper final 
	: public IOnSceneChangedListener
{
public:
	Looper();
	~Looper();
	bool Loop();

	void OnSceneChanged(const SceneID scene, const Parameter parameter, const bool stackClear) override;
	void OnScenePop() override;

private:
	std::stack<std::unique_ptr<SceneBase>> sceneStack;
	Fps fps;
};

