#pragma once

#include "Looper.h"
#include "SystemMain.h"
#include "Singleton.h"
#include "Timer.h"

#include <memory>

static
class DebugMode {
public:
	static void Init();
	static void Update();
	static void Draw();

	static bool IsDebugMode();
	static void SwitchDebugMode();

public:

private:

};