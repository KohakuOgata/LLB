#include "Utility.h"

#include "Define.h"

#include <DxLib.h>

double Utility::RandomFloatD()
{
	return static_cast<double>(GetRand(100000000)) / 100000000.0;
}

double Utility::RadNomalize(double value)
{
	while (value > Define::Pi)
		value -= 2 * Define::Pi;
	while (value <= -Define::Pi)
		value += 2 * Define::Pi;
	return value;
}
