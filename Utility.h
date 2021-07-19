#pragma once

#include <algorithm>

namespace Utility {
	template<typename T>
	T Max(const T& value1, const T& value2)
	{
		return (value1 < value2) ? value2 : value1;
	}

	template<typename T>
	T Min(const T& value1, const T& value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	template<typename T>
	T Clamp(const T& value, const T& low, const T& high)
	{
		return Max(low, Min(high, value));
	}

	//value‚ª [low, high] ‚È‚ç true
	template<typename T>
	T IsInRange(const T& value, const T& low, const T& high)
	{
		return Min(low, high) <= value && value <= Max(low, high);
	}

	template<typename T>
	T Square(const T& value) {
		return value * value;
	}

	template<typename T>
	T Lerp(const T& low, const T& high, const double& alpha) {
		return low + (high - low) * alpha;
	}

	template<typename T>
	double Map(const T& value, const T& low, const T& high) {
		return static_cast<double>((value - low) / (high - low));
	}

	//0.0 ~ 1.0‚Ì¬”’l‚ğƒ‰ƒ“ƒ_ƒ€‚Å•Ô‚·
	double RandomFloatD();

	//ŒÊ“x‚ğ³‹K‰»‚·‚é
	//(-PI, PI]
	double RadNomalize(double value);
}