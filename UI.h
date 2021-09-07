#pragma once
#include "GameObject.h"

#include <memory>

class AABB2D;

class UI :
	public GameObject
{
public:
	UI(SceneBase* _scene);
	~UI();
	void Update() override {};
	void Draw() override {};

protected:
	std::unique_ptr<AABB2D> screen;
};
