#pragma once
#include "GameObject.h"

#include <memory>

class SceneBase;
class Point2D;
class Double2;
class AABB2D;

class Stage
	: public GameObject
{
public:
	Stage(SceneBase* _scene);
	~Stage() = default;

	void Start() override;
	void Update() override;
	void Draw() override;

	const AABB2D& GetCollider() const;
	static Double2 GetStageSize();
	static Point2D GetStageCenter();

	void Restart();

private:

public:
	const static Double2 StageSize;

private:
	std::unique_ptr<AABB2D> collider;

};

