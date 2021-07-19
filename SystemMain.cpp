#include "SystemMain.h"

#include "Config.h"
#include "Looper.h"
#include "Input.h"
#include "Primitive2D.h"
#include "DebugMode.h"
#include "Color.h"

#include <DxLib.h>
#include <iostream>

void InputInit();
void ColorInit();
void ConfigInit();

/*!
* @brief DX���C�u������Q�[���̏�������
*/
bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);										//�E�B���h�E���m���A�N�e�B�u���Ɏ��s�𑱂��邩
	SetWindowSizeChangeEnableFlag(TRUE);						//�E�B���h�E�T�C�Y�����R�ɕύX�ł��邩
	SetOutApplicationLogValidFlag(FALSE);						//���O�o�͂��邩
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//�t���X�N���[�����ɏc������ێ����邩
	SetWindowText("LLB");										//�E�B���h�E�^�C�g��
	ChangeWindowMode(TRUE);										//�E�B���h�E���[�h���ǂ���
	SetWindowSizeExtendRate(1.0);								//�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;									//�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
	SetGraphMode(1920, 1080, COLOR_BIT);						//�Q�[����ʂ̉𑜓x
	SetBackgroundColor(255, 255, 255);							//�w�i�F
	if (DxLib_Init()) {											//DX���C�u��������������
		return false;											//�ُ�I�������瑦���ɂ�߂�
	}
	SetDrawScreen(DX_SCREEN_BACK);//����ʏ�����ݒ肷��
	ColorInit();
	ConfigInit();
	InputInit();
	DebugMode::Init();
	return true;
}

/*!
* @brief DX���C�u������Q�[���̏I������
*/
void SystemMain::finalize() const
{
	DxLib_End();
}

/*!
* @brief ���C������
*/
void SystemMain::main() const
{
	Looper looper;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !clsDx()) {
		int x, y;
		GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
		if (!looper.Loop()) {
			break;
		}
	}
}