#pragma once

#include "InputID.h"

#include <DxLib.h>
#include <initializer_list>

class Double2;
class Point2D;

class Input {

	//���C���̏�������1�x�����Ă�
	friend void InputInit();

	//���C�����[�v�Ŗ��t���[���Ă�
	friend void InputUpdate();

private:
	Input() = default;
	~Input() = default;

	static void Init();
	
	static void Update();

public:
	//�A�i���O�X�e�B�b�N�̖����͈͂�ݒ肷��
	//�A�i���O�擾���p�iDouble2�ŕԂ��Ă����j
	//0.0 �` 1.0��n��
	static void SetJoypadStickDeadZoneAnalog (const double& left, const double& right, const int& inputType = DX_INPUT_PAD1);

	//�A�i���O�X�e�B�b�N�̖����͈͂�ݒ肷��
	//�f�W�^���擾���p�iGetPush�n�Ŏ���j
	//0.0 �` 1.0��n��
	static void SetJoypadStickDeadZoneDigital(const double& left, const double& right, const int& inputType = DX_INPUT_PAD1);

	//�����Ŏw�肳�ꂽ�{�^�����A�����ĉ�����Ă���t���[������Ԃ�
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> �i�p�b�h���͎擾���Ɏg�p�j
	static double GetPushStay(const InputID& inputID);

	//�����Ŏw�肳�ꂽ�{�^�����������u�Ԃ���(true)��Ԃ�
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> �i�p�b�h���͎擾���Ɏg�p�j
	static bool GetPushDown(const InputID& inputID);

	//�����Ŏw�肳�ꂽ�{�^���𗣂����u�Ԃ���(true)��Ԃ�
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> �i�p�b�h���͎擾���Ɏg�p�j
	static bool GetPushUp(const InputID& inputID, unsigned int* const outPush = nullptr);

	//�}�E�X�J�[�\���̉�ʓ����W��Point2D�^�ŕԂ�
	static Point2D GetMousePos(void);

	//���̃t���[���ł̃}�E�X�z�C�[���̉�]�ʂ�Ԃ�
	static int GetMouseRot(void);
	
	//�����Ŏw�肳�ꂽ���ׂẴ{�^���������ɉ����ꂽ�ŏ��̃t���[������(true)��Ԃ�
	static bool GetMultiplePushDown(const std::initializer_list<InputID> inputCodes);

	static double GetJoypadLeftTrigger(const int& inputType = DX_INPUT_PAD1);
	static double GetJoypadRightTrigger(const int& inputType = DX_INPUT_PAD1);
	static Double2 GetJoypadLeftStick(const int& inputType = DX_INPUT_PAD1);
	static Double2 GetJoypadRightStick(const int& inputType = DX_INPUT_PAD1);

	static void PrintJoypadAll(const int& inputType = DX_INPUT_PAD1);
};
