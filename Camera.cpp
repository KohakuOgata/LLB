#include "Camera.h"
#include "Primitive2D.h"
#include "SceneBase.h"
#include "Config.h"
#include "Stage.h"
#include "VInput.h"

Camera::Camera(SceneBase* _pScene):
	GameObject(_pScene), flame(std::make_unique<AABB2D>(Point2D::Zero, Config::WindowSize))
{
}

void Camera::Start()
{
	SetCenterPos(GetScene()->FindGameObject<Stage>()->GetStageCenter());
}

void Camera::Update()
{
	//*flame += Vec2(VInput::GetIns()->GetVAxis(VAxisID::Horizontal), 0);
}

const AABB2D& Camera::GetFlame() const
{
	return *flame;
}

void Camera::SetCenterPos(const Point2D& newCenterPos)
{
	flame->Center(newCenterPos);
}
