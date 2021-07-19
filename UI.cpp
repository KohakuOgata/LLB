
#include "UI.h"

#include "Primitive2D.h"
#include "Config.h"

UI::UI(SceneBase* _scene) :
	GameObject(_scene),
	screen(std::make_unique<AABB2D>(Config::WindowSize))
{
}

UI::~UI()
{
}
