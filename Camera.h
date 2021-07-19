#pragma once
#include "GameObject.h"

#include "Stage.h"

#include <memory>

class Point2D;
class AABB2D;

class Camera
	:public GameObject
{
public:
	Camera(SceneBase* _pScene);

	void Start() override;
	void Update() override;

	const AABB2D& GetFlame() const;

private:
	void SetCenterPos(const Point2D& newCenterPos);
private:
	std::unique_ptr<AABB2D> flame;
};