#include "VAxis.h"

#include "Button.h"
#include "VButton.h"
#include "Time.h"
#include "Input.h"

#include <algorithm>
#include <assert.h>

const double VAxis::DefaultGravity = 100.0;
const double VAxis::DefaultSensitivity = 100.0;
const bool VAxis::DefaultSnap = true;

VAxis::VAxis()
	:plusButton(std::make_unique<VButton>()), minusButton(std::make_unique<VButton>()), joypadAxises(std::make_unique<std::list<double*>>()),
	gravity(DefaultGravity), sensitivity(DefaultSensitivity), snap(DefaultSnap),
	isAnalogInput(false), value(0.0)
{
}

//VAxis::VAxis(const std::initializer_list<InputID> _plusButtonInputs, const std::initializer_list<InputID> _minusButtonInputs, const std::initializer_list<double*> _joypadAxises)
//	:plusButton(std::make_unique<VButton>(_plusButtonInputs)), minusButton(std::make_unique<VButton>(_minusButtonInputs)), joypadAxises(_joypadAxises),
//	gravity(DefaultGravity), sensitivity(DefaultSensitivity), snap(DefaultSnap),
//	isAnalogInput(false), value(0.0)
//{
//}

void VAxis::Update()
{
	double tempVal = 0.0;
	isAnalogInput = false;
	for (const auto& it : *joypadAxises) {
		if (*it == 0.0)
			continue;
		isAnalogInput = true;
		if (*it * tempVal < 0.0 && snap) {
			value = 0.0;
			return;
		}
		tempVal += *it;
	}
	if (isAnalogInput) {
		value = tempVal;
		return;
	}

	plusButton->Update();
	minusButton->Update();


	if (Input::GetPushStay(InputID::KeyS))
		int i = 0;

	bool isPlusPushed = plusButton->button->GetPushStay();
	bool isMinusPushed = minusButton->button->GetPushStay();

	const int plus_minus = (isPlusPushed << 1) | (isMinusPushed);

	switch (plus_minus)
	{
	case 0:	//プラスもマイナスも押されていない
		if (value == 0.0)
			return;
		if (value > 0.0)
			value = max(0.0, value - gravity * Time::DeltaTime());
		else
			value = min(0.0, value + gravity * Time::DeltaTime());
		return;
	case 1:	//マイナスだけ押されている
		if (value > 0.0 && snap) {
			value = 0.0;
			return;
		}
		value = max(-1.0, value - sensitivity * Time::DeltaTime());
		return;
	case 2:	//プラスだけ押されている
		if (value < 0.0 && snap) {
			value = 0.0;
			return;
		}
		value = min(1.0, value + sensitivity * Time::DeltaTime());
		return;
	case 3:	//プラスもマイナスも押されている
		if (snap)
			value = 0.0;
		return;
	default:
		int a = 0;
		break;
	}
}

void VAxis::AddPlusButton(const InputID plusInput)
{
	plusButton->AddInput(plusInput);
}

void VAxis::AddPlusButton(const std::initializer_list<InputID> plusInputs)
{
	plusButton->AddInput(plusInputs);
}

void VAxis::AddMinusButton(const InputID minusInput)
{
	minusButton->AddInput(minusInput);
}

void VAxis::AddMinusButton(const std::initializer_list<InputID> minusInputs)
{
	minusButton->AddInput(minusInputs);
}

void VAxis::AddJoypadAxises(double* const joypadAxis)
{		
	for (auto it = joypadAxises->begin(); it != joypadAxises->end(); it++)
		if (*it == joypadAxis)
			return;
	
	joypadAxises->push_back(joypadAxis);
}

void VAxis::AddJoypadAxises(const std::initializer_list<double*> joypadAxises)
{
	for (auto axisToAdd : joypadAxises) {
		if (std::find(this->joypadAxises->begin(), this->joypadAxises->end(), axisToAdd) != this->joypadAxises->end())
			continue;
		this->joypadAxises->push_back(axisToAdd);
	}
}

void VAxis::ErasePlusButton(const InputID plusInput)
{
	plusButton->EraseInput(plusInput);
}

void VAxis::ErasePlusButton(std::initializer_list<InputID> plusInputs)
{
	plusButton->EraseInput(plusInputs);
}

void VAxis::EraseMinusButton(const InputID minusInput)
{
	minusButton->EraseInput(minusInput);
}

void VAxis::EraseMinusButton(const std::initializer_list<InputID> minusInputs)
{
	minusButton->EraseInput(minusInputs);
}

void VAxis::EraseJoypadAXises(double* joypadAxis)
{
	joypadAxises->erase(std::find(joypadAxises->begin(), joypadAxises->end(), joypadAxis));
}

void VAxis::EraseJoypadAXises(const std::initializer_list<double*> joypadAxises)
{
	for (const auto& axisToErase : joypadAxises) {
		this->joypadAxises->remove(axisToErase);
	}
}

void VAxis::ClearPlusButtons()
{
	plusButton->ClearInput();
}

void VAxis::ClearMinusButtons()
{
	minusButton->ClearInput();
}

void VAxis::ClearJoypadAxises()
{
	joypadAxises->clear();
}

void VAxis::SetGravity(const double _gravity)
{
	gravity = max(0.0, _gravity);
}

void VAxis::SetSensitivity(const double _sensitivity)
{
	sensitivity = max(0.0, _sensitivity);
}

void VAxis::SetSnap(const bool _snap)
{
	snap = _snap;
}

double VAxis::Value() const
{
	return value;
}