#pragma once
enum class ColorID {
	White  ,
	Black  ,
	Gray   ,
	Red    ,
	Green  ,
	Blue   ,
	Yellow ,
	Cyan   ,
	Magenta,

	Num,
};

static class Color
{
	friend void ColorInit();

public:
	static unsigned int Get(const ColorID id);

private:
	static void Init();

private:
	static unsigned int colors[static_cast<size_t>(ColorID::Num)];
};