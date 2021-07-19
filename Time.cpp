#include "Time.h"

#include <DxLib.h>

double Time::deltaTime = 0.0;
double Time::lastTime = 0.0;

void Time::Update()
{
	const double nowTimeSec = static_cast<double>(GetNowCount()) / 1000.0;
	deltaTime = nowTimeSec - lastTime;
	lastTime = nowTimeSec;
}

double Time::DeltaTime()
{
	return deltaTime;
	return 1.0 / 60.0;
}

void TimeUpdate()
{
	Time::Update();
}
