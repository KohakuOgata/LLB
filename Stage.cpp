#include "Stage.h"

#include "Primitive2D.h"
#include "Config.h"
#include "SceneBase.h"
#include "Camera.h"

#include <memory>
#include <DxLib.h>

const Double2 Stage::StageSize = Double2(1260.0, 770.0);

Stage::Stage(SceneBase* _scene):
	GameObject(_scene),
	collider(std::make_unique<AABB2D>(StageSize))
{
}

void Stage::Start()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	const Camera* Cam = GetScene()->FindGameObject<Camera>();
	const Point2D CamLT = Cam->GetFlame().LeftTop();
	DrawBox(0 - CamLT.x, (Config::WindowSize.y - StageSize.y) / 2, StageSize.x - CamLT.x, (Config::WindowSize.y + StageSize.y) / 2, Color::Get(ColorID::Magenta), false);
}

const AABB2D& Stage::GetCollider() const
{
	return *collider;
}

Double2 Stage::GetStageSize()
{
	return StageSize;
}

Point2D Stage::GetStageCenter()
{
	return StageSize / 2;
}

void Stage::Restart()
{
}
