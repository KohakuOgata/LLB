#include "DebugMode.h"

#include "Config.h"
#include "Timer.h"
#include "Input.h"
#include "Fps.h"

namespace {
	bool isDebugMode = false;
}

bool DebugMode::IsDebugMode()
{
	return isDebugMode;
}

void DebugMode::SwitchDebugMode()
{
	isDebugMode = !isDebugMode;
}

void DebugMode::Init()
{
	isDebugMode = Config::InitialDebugMode;
}

void DebugMode::Update()
{
}

void DebugMode::Draw()
{
}
