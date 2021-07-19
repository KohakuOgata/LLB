#pragma once

static class Time
{
	friend void TimeUpdate();
private:
	static void Update();
	
public:
	static double DeltaTime();
	
private:
	static double lastTime;
	static double deltaTime;
};

