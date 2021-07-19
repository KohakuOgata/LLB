#pragma once

static class Define {
public:
	const static double Pi;	//â~é¸ó¶
	const static double Epsilon;//åÎç∑
	const static int StageWidth;
	const static int StageHeight;

	enum class EController {
		Pad1,
		Pad2,
		Pad3,
		Pad4,
		Keyboard
	};
	class ETeam {
	public:
		ETeam() : value(None) {}
		ETeam(const int team) : value(team) {}
		int value;
		enum {
			None,
			Red,
			Blue,
			Yellow,
			Green
		};
		operator int() { return value; }
	};
	enum class EDirection {
		None,
		Up,
		Down,
		Left,
		Right
	};
	const static int InvalidHandle = -1;
};