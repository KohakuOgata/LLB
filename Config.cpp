#include "Config.h"

#include "Primitive2D.h"

bool Config::InitialDebugMode = true;
Double2 Config::WindowSize = Double2();
Point2D Config::WindowCenter = Double2();
int Config::FPS = 60;

void ConfigInit()
{
	Config::Init();
}

void Config::Init()
{
	InitialDebugMode = true;
	WindowSize = { 1920, 1080 };
	WindowCenter = Config::WindowSize / 2;

	FPS = 60;
}
