#include "VInput.h"

#include "VButton.h"
#include "VAxis.h"
#include "InputID.h"
#include "Input.h"
#include "Primitive2D.h"
#include "Button.h"

namespace {
	double padLThumbX = 0.0;
	double padLThumbY = 0.0;
}

VInput::VInput()
{
	for (auto& i : vButtons) {
		auto buf = std::make_unique<VButton>();
		i = std::move(buf);
	}
	AddVButtonInput(VButtonID::Jump, { InputID::PadA, InputID::KeySpace });
	AddVButtonInput(VButtonID::Dash, { InputID::PadX, InputID::KeyLShift });
	AddVButtonInput(VButtonID::Enter, { InputID::PadA, InputID::KeySpace, InputID::KeyReturn });
	AddVButtonInput(VButtonID::Cancel, { InputID::PadB, InputID::KeyEscape, InputID::KeyBack });
	AddVButtonInput(VButtonID::Up, { InputID::PadDPadUp, InputID::PadRightThumbTiltUp, InputID::KeyUp, InputID::KeyW });
	AddVButtonInput(VButtonID::Down, { InputID::PadDPadDown, InputID::PadRightThumbTiltDown, InputID::KeyDown, InputID::KeyS });
	AddVButtonInput(VButtonID::Left, { InputID::PadDPadLeft, InputID::PadRightThumbTiltLeft, InputID::KeyLeft, InputID::KeyA });
	AddVButtonInput(VButtonID::Right, { InputID::PadDPadRight, InputID::PadRightThumbTiltRight, InputID::KeyRight, InputID::KeyD });
	AddVButtonInput(VButtonID::Escape, { InputID::PadStart, InputID::KeyEscape });
	AddVButtonInput(VButtonID::Interact, { InputID::PadY, InputID::KeyF });
	AddVButtonInput(VButtonID::Grab, { InputID::PadRightTrigger, InputID::KeyReturn });

	for (auto& i : vAxises) {
		auto buf = std::make_unique<VAxis>();
		i = std::move(buf);
	}

	SetVAxis(
		VAxisID::Horizontal,
		{ InputID::PadDPadRight, InputID::KeyD, InputID::KeyRight },
		{ InputID::PadDPadLeft, InputID::KeyA, InputID::KeyLeft },
		{ &padLThumbX }
	);

	SetVAxis(
		VAxisID::Vertical,
		{ InputID::PadDPadDown, InputID::KeyS, InputID::KeyDown },
		{ InputID::PadDPadUp, InputID::KeyW, InputID::KeyUp },
		{ &padLThumbY }
	);
}

VInput::~VInput()
{
	
}

void VInput::Update()
{
	padLThumbX = Input::GetJoypadLeftStick().x;
	padLThumbY = Input::GetJoypadLeftStick().y;

	for (auto& it : vButtons)
		it->Update();
	for (auto& it : vAxises)
		it->Update();
}

void VInput::AddVButtonInput(const VButtonID vButtonName, std::initializer_list<InputID> inputIDs)
{
	if (vButtonName == VButtonID::Num)
		return;
	const unsigned int idx = static_cast<unsigned int>(vButtonName);
	vButtons.at(idx)->AddInput(inputIDs);
}

void VInput::AddVAxisPlusButton(const VAxisID vAxisID, std::initializer_list<InputID> idsToAdd)
{
	if (vAxisID == VAxisID::Num)
		return;
	const unsigned int idx = static_cast<unsigned int>(vAxisID);
	vAxises.at(idx)->AddPlusButton(idsToAdd);
}

void VInput::AddVAxisMinusButton(const VAxisID vAxisID, std::initializer_list<InputID> idsToAdd)
{
	if (vAxisID == VAxisID::Num)
		return;
	const unsigned int idx = static_cast<unsigned int>(vAxisID);
	vAxises.at(idx)->AddMinusButton(idsToAdd);
}

void VInput::AddVAxisJoypadAxis(const VAxisID vAxisID, std::initializer_list<double*> joypadAxisesToAdd)
{
	if (vAxisID == VAxisID::Num)
		return;
	const unsigned int idx = static_cast<unsigned int>(vAxisID);
	vAxises.at(idx)->AddJoypadAxises(joypadAxisesToAdd);
}

void VInput::SetVAxis(const VAxisID vAxisID, std::initializer_list<InputID> idsToAddPlus, std::initializer_list<InputID> idsToAddMinus, std::initializer_list<double*> joypadAxisesToAdd)
{
	if (vAxisID == VAxisID::Num)
		return;
	const unsigned int idx = static_cast<unsigned int>(vAxisID);
	vAxises.at(idx)->ClearPlusButtons();
	vAxises.at(idx)->ClearMinusButtons();
	vAxises.at(idx)->ClearJoypadAxises();
	vAxises.at(idx)->AddPlusButton(idsToAddPlus);
	vAxises.at(idx)->AddMinusButton(idsToAddMinus);
	vAxises.at(idx)->AddJoypadAxises(joypadAxisesToAdd);
}

void VInputUpdate()
{
	VInput::GetIns()->Update();
}

double VInput::GetPushStay(VButtonID vButtonName) const
{
	return vButtons.at(static_cast<size_t>(vButtonName))->button->GetPushStay();
}

bool VInput::GetPushDown(VButtonID vButtonName) const
{
	return vButtons.at(static_cast<size_t>(vButtonName))->button->GetPushDown();
}

bool VInput::GetPushUp(VButtonID vButtonName) const
{
	return vButtons.at(static_cast<size_t>(vButtonName))->button->GetPushUp();
}

double VInput::GetVAxis(VAxisID vAxisName) const
{
	return vAxises.at(static_cast<size_t>(vAxisName))->Value();
}
