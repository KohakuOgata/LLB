#pragma once

#include "Singleton.h"

#include <string>
#include <array>
#include <vector>
#include <memory>

enum class InputID;

enum class VButtonID {
	Jump,
	Dash,
	Enter,
	Cancel,
	Up,
	Down,
	Left,
	Right,
	Escape,
	Interact,
	Grab,

	Num
};

enum class VAxisID {
	Horizontal,
	Vertical,

	Num
};

class VButton;
class VAxis;

class VInput : public Singleton<VInput> {

	friend void VInputUpdate();
	friend Singleton<VInput>;

public:
	double GetPushStay(VButtonID vButtonName) const;
	bool GetPushDown(VButtonID vButtonName) const;
	bool GetPushUp(VButtonID vButtonName) const;
	double GetVAxis(VAxisID vAxisName) const;

private:
	VInput();
	~VInput();
	void Update();
	void AddVButtonInput(const VButtonID vButtonID, std::initializer_list<InputID> idsToAdd);
	void AddVAxisPlusButton(const VAxisID vAxisID, std::initializer_list<InputID> idsToAdd);
	void AddVAxisMinusButton(const VAxisID vAxisID, std::initializer_list<InputID> idsToAdd);
	void AddVAxisJoypadAxis(const VAxisID vAxisID, std::initializer_list<double*> joypadAxisesToAdd);
	void SetVAxis(const VAxisID vAxisID, std::initializer_list<InputID> idsToSetPlus, std::initializer_list<InputID> idsToSetMinus, std::initializer_list<double*> joypadAxisesToSet);

	std::array<std::unique_ptr<VButton>, static_cast<size_t>(VButtonID::Num)> vButtons;
	std::array<std::unique_ptr<VAxis>, static_cast<size_t>(VButtonID::Num)> vAxises;
};