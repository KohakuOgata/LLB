#include "Input.h"

#include "Utility.h"
#include "Primitive2D.h"
#include "Button.h"

#include <DxLib.h>
#include <algorithm>
#include <initializer_list>

namespace {

	//キー更新
	void InputKey();

	//マウス更新
	void InputMouse();

	//ジョイパッド更新
	void InputJoypad();

	Button key[256];
	Button click[8];

	int MouseX = 0;
	int MouseY = 0;

	int MouseRot = 0;

	Button joypadButton[16][26];
	double joypadLeftTrigger[16];
	double joypadRightTrigger[16];
	Vec2 joypadLeftStick[16];
	Vec2 joypadRightStick[16];

	double stickDeadZoneAnalogLeft[16];
	double stickDeadZoneAnalogRight[16];
	double stickDeadZoneDigitalLeft[16];
	double stickDeadZoneDigitalRight[16];
	char joypadNum = 16;

	const double InitialAnalogDeadZone = 0.15;
	const double InitialDigitalDeadZone = 0.35;
}

void Input::Init()
{
	joypadNum = GetJoypadNum();
	for (int i = 0; i < 16; i++) {
		SetJoypadStickDeadZoneAnalog(InitialAnalogDeadZone, InitialAnalogDeadZone, i + 1);
		SetJoypadStickDeadZoneDigital(InitialDigitalDeadZone, InitialDigitalDeadZone, i + 1);
	}
}

void Input::Update()
{
	if (GetMultiplePushDown({ InputID::KeyR, InputID::KeyC })) {
		ReSetupJoypad();
		joypadNum = GetJoypadNum();
	}
	MouseRot = GetMouseWheelRotVol();
	InputKey();
	InputMouse();
	InputJoypad();
}

void Input::SetJoypadStickDeadZoneAnalog(const double& left, const double& right, const int& inputType)
{
	stickDeadZoneAnalogLeft[inputType - 1] = Utility::Clamp(left, 0.0, 1.0);
	stickDeadZoneAnalogRight[inputType - 1] = Utility::Clamp(right, 0.0, 1.0);
}

void Input::SetJoypadStickDeadZoneDigital(const double& left, const double& right, const int& inputType)
{
	stickDeadZoneDigitalLeft[inputType - 1] = Utility::Clamp(left, 0.0, 1.0);
	stickDeadZoneDigitalRight[inputType - 1] = Utility::Clamp(right, 0.0, 1.0);
}

double Input::GetPushStay(const InputID& inputCode)
{
	const int intCode = static_cast<int>(inputCode);
	if (inputCode < InputID::MouseLeft)
		return key[intCode].GetPushStay();
	if (inputCode < InputID::PadDPadUp)
		for (int i = 0; i < 8; i++)
			if (intCode & (1 << i))
				return click[i].GetPushStay();
	if (inputCode < InputID::Pad1DPadUp) {
		double push = 0;
		const int buttonIdx = intCode & 0x0fff;
		for (int pad = 0; pad < 4; pad++)
			push = max(joypadButton[pad][buttonIdx].GetPushStay(), push);
		return push;
	}
	if (inputCode <= InputID::Pad4LeftTrigger) {
		return joypadButton[((intCode & 0xf000) >> 12) - 3][intCode & 0x0fff].GetPushStay();
	}
	abort();
}

bool Input::GetPushDown(const InputID& inputCode)
{
	const int intCode = static_cast<int>(inputCode);
	if (inputCode < InputID::MouseLeft)
		return key[intCode].GetPushDown();
	if (inputCode < InputID::PadDPadUp)
		for (int i = 0; i < 8; i++)
			if (intCode & (1 << i))
				return click[i].GetPushDown();
	if (inputCode < InputID::Pad1DPadUp) {
		const int buttonIdx = intCode & 0x0fff;
		for (int pad = 0; pad < 4; pad++)
			if (joypadButton[pad][buttonIdx].GetPushDown())
				return true;
		return false;
	}
	if (inputCode <= InputID::Pad4LeftTrigger) {
		return joypadButton[((intCode & 0xf000) >> 12) - 3][intCode & 0x0fff].GetPushDown();
	}
	abort();
}

bool Input::GetPushUp(const InputID& inputCode, unsigned int* const outPush)
{
	const int intCode = static_cast<int>(inputCode);
	if (inputCode < InputID::MouseLeft) {
		if (outPush != nullptr)
			*outPush = key[intCode].GetPushOnPushUp();
		return key[intCode].GetPushUp();
	}
	if (inputCode < InputID::PadDPadUp)
		for (int i = 0; i < 8; i++)
			if (intCode & (1 << i)) {
				if (outPush != nullptr)
					*outPush = click[i].GetPushOnPushUp();
				return click[i].GetPushUp();
			}
	if (inputCode < InputID::Pad1DPadUp) {
		const int buttonIdx = intCode & 0x0fff;
		for (int pad = 0; pad < 4; pad++)
			if (joypadButton[pad][buttonIdx].GetPushUp()) {
				if(outPush != nullptr)
					*outPush = joypadButton[pad][buttonIdx].GetPushOnPushUp();
				return true;
			}
		return false;
	}
	if (inputCode <= InputID::Pad4LeftTrigger) {
		if (joypadButton[(intCode & 0xf000) >> 6][intCode & 0x0fff].GetPushUp()) {
			if (outPush != nullptr)
				*outPush = joypadButton[((intCode & 0xf000) >> 12) - 3][intCode & 0x0fff].GetPushOnPushUp();
			return true;
		}
		return false;
	}
	abort();
}

Point2D Input::GetMousePos(void)
{
	Point2D pos(MouseX, MouseY);

	return pos;
}

int Input::GetMouseRot(void)
{
	return MouseRot;
}

bool Input::GetMultiplePushDown(const std::initializer_list<InputID> inputCodes)
{
	bool anyPushDown = false;
	for (const InputID inputCode : inputCodes) {
		if (GetPushStay(inputCode) == 0)
			return false;
		if (GetPushDown(inputCode))
			anyPushDown = true;
	}
	return anyPushDown;
}

double Input::GetJoypadLeftTrigger(const int& inputType)
{
	return joypadLeftTrigger[inputType - 1];
}

double Input::GetJoypadRightTrigger(const int& inputType)
{
	return joypadRightTrigger[inputType - 1];
}

Double2 Input::GetJoypadLeftStick(const int& inputType)
{
	return joypadLeftStick[inputType - 1];
}

Double2 Input::GetJoypadRightStick(const int& inputType)
{
	return joypadRightStick[inputType - 1];
}

void Input::PrintJoypadAll(const int& inputType)
{
	const int padNo = inputType - 1;
	printfDx("\
Pad%d\
DUp:%.2f, DDown:%.2f, DLeft:%.2f, DRight:%.2f,\n\
Start:%.2f, Back:%.2f, LSClick:%.2f, RSClick:%.2f, LB:%.2f, RB:%.2f,\n\
A:%.2f, B:%.2f, X:%.2f, Y:%.2f,\n\
LSTilt:%.2f, LSUp:%.2f, LSDown:%.2f, LSLeft:%.2f, LSRight:%.2f,\n\
RSTilt:%.2f, RSUp:%.2f, RSDown:%.2f, RSLeft:%.2f, RSRight:%.2f,\n\
LTOn:%.2f, RTOn:%.2f,\n\
LT:%+.2f, RT:%+.2f,\n\
LSX:%+.2f, LSY:%+.2f, RSX:%+.2f, RSY:%+.2f\n\n",
inputType,
(float)joypadButton[padNo][static_cast<int>(InputID::PadDPadUp) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadDPadDown) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadDPadLeft) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadDPadRight) & 0x0fff].GetPushStay(),
(float)joypadButton[padNo][static_cast<int>(InputID::PadStart) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadBack) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbClick) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbClick) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftShoulder) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightShoulder) & 0x0fff].GetPushStay(),
(float)joypadButton[padNo][static_cast<int>(InputID::PadA) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadB) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadX) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadY) & 0x0fff].GetPushStay(),
(float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbTilt) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbTiltUp) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbTiltDown) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbTiltLeft) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadLeftThumbTiltRight) & 0x0fff].GetPushStay(),
(float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbTilt) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbTiltUp) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbTiltDown) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbTiltLeft) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightThumbTiltRight) & 0x0fff].GetPushStay(),
(float)joypadButton[padNo][static_cast<int>(InputID::PadLeftTrigger) & 0x0fff].GetPushStay(), (float)joypadButton[padNo][static_cast<int>(InputID::PadRightTrigger) & 0x0fff].GetPushStay(),
(float)joypadLeftTrigger[padNo], (float)joypadRightTrigger[padNo],
(float)joypadLeftStick[padNo].x, (float)joypadLeftStick[padNo].y, (float)joypadRightStick[padNo].x, (float)joypadRightStick[padNo].y);
}

namespace {
	void InputKey()
	{
		static char buf[256];

		//すべてのキーの状態を格納
		GetHitKeyStateAll(buf);

		for (int i = 0; i < 256; ++i)
			key[i].Update(buf[i]);
	}

	void InputMouse()
	{
		GetMousePoint(&MouseX, &MouseY);

		for (int i = 0; i < 8; ++i)
			click[i].Update(GetMouseInput() & (1 << i));
	}

	void InputJoypad()
	{
		for (int i = 0; i < joypadNum; ++i) {
			XINPUT_STATE buf;
			GetJoypadXInputState(i + 1, &buf);
			for (int j = 0; j < 10; j++) {
				joypadButton[i][j].Update(buf.Buttons[j]);
			}
			for (int j = 12; j < 16; j++) {
				joypadButton[i][j - 2].Update(buf.Buttons[j]);
			}
			const double rawLeftStick = Vec2((double)buf.ThumbLX / 32768, -(double)buf.ThumbLY / 32768).Length();
			const bool leftStickOnAnalog = rawLeftStick > stickDeadZoneAnalogLeft[i];
			const bool leftStickOnDigital = rawLeftStick > stickDeadZoneDigitalLeft[i];
			const double rawRightStick = Vec2((double)buf.ThumbRX / 32768, -(double)buf.ThumbRY / 32768).Length();
			const bool rightStickOnAnalog = rawRightStick > stickDeadZoneAnalogRight[i];
			const bool rightStickOnDigital = rawRightStick > stickDeadZoneDigitalRight[i];
			joypadButton[i][static_cast<int>(InputID::PadLeftThumbTilt)       & 0x0fff].Update(leftStickOnDigital);
			joypadButton[i][static_cast<int>(InputID::PadLeftThumbTiltUp)     & 0x0fff].Update(leftStickOnDigital && buf.ThumbLY >= -buf.ThumbLX && buf.ThumbLY >= buf.ThumbLX);
			joypadButton[i][static_cast<int>(InputID::PadLeftThumbTiltDown)   & 0x0fff].Update(leftStickOnDigital && buf.ThumbLY <= -buf.ThumbLX && buf.ThumbLY <= buf.ThumbLX);
			joypadButton[i][static_cast<int>(InputID::PadLeftThumbTiltLeft)   & 0x0fff].Update(leftStickOnDigital && buf.ThumbLY <= -buf.ThumbLX && buf.ThumbLY >= buf.ThumbLX);
			joypadButton[i][static_cast<int>(InputID::PadLeftThumbTiltRight)  & 0x0fff].Update(leftStickOnDigital && buf.ThumbLY >= -buf.ThumbLX && buf.ThumbLY <= buf.ThumbLX);
			joypadButton[i][static_cast<int>(InputID::PadRightThumbTilt)      & 0x0fff].Update(rightStickOnDigital);
			joypadButton[i][static_cast<int>(InputID::PadRightThumbTiltUp)    & 0x0fff].Update(rightStickOnDigital && buf.ThumbRY >= -buf.ThumbRX && buf.ThumbRY >= buf.ThumbRX);
			joypadButton[i][static_cast<int>(InputID::PadRightThumbTiltDown)  & 0x0fff].Update(rightStickOnDigital && buf.ThumbRY <= -buf.ThumbRX && buf.ThumbRY <= buf.ThumbRX);
			joypadButton[i][static_cast<int>(InputID::PadRightThumbTiltLeft)  & 0x0fff].Update(rightStickOnDigital && buf.ThumbRY <= -buf.ThumbRX && buf.ThumbRY >= buf.ThumbRX);
			joypadButton[i][static_cast<int>(InputID::PadRightThumbTiltRight) & 0x0fff].Update(rightStickOnDigital && buf.ThumbRY >= -buf.ThumbRX && buf.ThumbRY <= buf.ThumbRX);
			joypadButton[i][static_cast<int>(InputID::PadRightTrigger)        & 0x0fff].Update(buf.RightTrigger);
			joypadButton[i][static_cast<int>(InputID::PadLeftTrigger)         & 0x0fff].Update(buf.LeftTrigger);
			joypadLeftTrigger[i] = (double)buf.LeftTrigger / 255;
			joypadRightTrigger[i] = (double)buf.RightTrigger / 255;
			joypadLeftStick[i] = leftStickOnAnalog ? Vec2((double)buf.ThumbLX / 32768, -(double)buf.ThumbLY / 32768) : Vec2::Zero;
			joypadRightStick[i] = rightStickOnAnalog ? Vec2((double)buf.ThumbRX / 32768, -(double)buf.ThumbRY / 32768) : Vec2::Zero;
		}
	}
}

void InputInit()
{
	Input::Init();
}

void InputUpdate()
{
	Input::Update();
}
