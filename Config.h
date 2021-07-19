#pragma once

class Double2;
class Point2D;

static class Config final {
	friend void ConfigInit();
private:
	static void Init();

public:
	static bool InitialDebugMode;
	static Double2 WindowSize;
	static Point2D WindowCenter;
	
	static int FPS;
};