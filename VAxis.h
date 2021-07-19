#pragma once

#include <memory>
#include <list>

enum class InputID;
class VButton;

class VAxis {
public:
	VAxis();

	void Update();
	void AddPlusButton(const InputID plusInput);
	void AddPlusButton(const std::initializer_list<InputID> plusInputs);
	void AddMinusButton(const InputID minusInput);
	void AddMinusButton(const std::initializer_list<InputID> minusInputs);
	void AddJoypadAxises(double* const joypadAxis);
	void AddJoypadAxises(const std::initializer_list<double*> joypadAxises);
	void ErasePlusButton(const InputID plusInput);
	void ErasePlusButton(std::initializer_list<InputID> plusInputs);
	void EraseMinusButton(const InputID minusInput);
	void EraseMinusButton(const std::initializer_list<InputID> minusInputs);
	void EraseJoypadAXises(double* joypadAxis);
	void EraseJoypadAXises(const std::initializer_list<double*> joypadAxises);
	void ClearPlusButtons();
	void ClearMinusButtons();
	void ClearJoypadAxises();

	void SetGravity(const double _gravity);
	void SetSensitivity(const double _sensitivity);
	void SetSnap(const bool _snap);

	double Value() const;
private:
	std::unique_ptr<VButton> plusButton;
	std::unique_ptr<VButton> minusButton;
	std::unique_ptr<std::list<double*>> joypadAxises;

	double gravity;
	double sensitivity;
	bool snap;

	bool isAnalogInput;
	double value;	//-1.0 ~ 1.0

	static const double DefaultGravity;
	static const double DefaultSensitivity;
	static const bool DefaultSnap;
};