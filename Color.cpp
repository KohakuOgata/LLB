#include "Color.h"

#include <DxLib.h>

unsigned int Color::colors[static_cast<size_t>(ColorID::Num)] = { 0 };

void ColorInit()
{
	Color::Init();
}

unsigned int Color::Get(const ColorID id)
{
	if (id != ColorID::Num)
		return colors[static_cast<unsigned int>(id)];
	return colors[static_cast<unsigned int>(ColorID::White)];
}

void Color::Init()
{
	colors[static_cast<unsigned int>(ColorID::White)]   = GetColor(255, 255, 255);
	colors[static_cast<unsigned int>(ColorID::Black)]   = GetColor(0, 0, 0);
	colors[static_cast<unsigned int>(ColorID::Gray)]    = GetColor(127, 127, 127);
	colors[static_cast<unsigned int>(ColorID::Red)]     = GetColor(255, 0, 0);
	colors[static_cast<unsigned int>(ColorID::Green)]   = GetColor(0, 255, 0);
	colors[static_cast<unsigned int>(ColorID::Blue)]    = GetColor(0, 0, 255);
	colors[static_cast<unsigned int>(ColorID::Yellow)]  = GetColor(255, 255, 0);
	colors[static_cast<unsigned int>(ColorID::Cyan)]    = GetColor(0, 255, 255);
	colors[static_cast<unsigned int>(ColorID::Magenta)] = GetColor(255, 0, 255);
}