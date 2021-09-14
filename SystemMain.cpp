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
* @brief DXライブラリやゲームの初期処理
*/
bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);										//ウィンドウがノンアクティブ時に実行を続けるか
	SetWindowSizeChangeEnableFlag(TRUE);						//ウィンドウサイズを自由に変更できるか
	SetOutApplicationLogValidFlag(FALSE);						//ログ出力するか
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//フルスクリーン時に縦横比を維持するか
	SetWindowText("LLB");										//ウィンドウタイトル
	ChangeWindowMode(TRUE);										//ウィンドウモードかどうか
	SetWindowSizeExtendRate(1.0);								//ウィンドウサイズを変更したい時はここに倍率を指定する
	const int COLOR_BIT = 32;									//色のbit数。通常32で良いが軽くするなら16にする
	SetGraphMode(1920, 1080, COLOR_BIT);						//ゲーム画面の解像度
	SetBackgroundColor(255, 255, 255);							//背景色
	if (DxLib_Init()) {											//DXライブラリ初期化処理
		return false;											//異常終了したら即座にやめる
	}
	SetDrawScreen(DX_SCREEN_BACK);//裏画面処理を設定する
	ColorInit();
	ConfigInit();
	InputInit();
	DebugMode::Init();
	return true;
}

/*!
* @brief DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{
	DxLib_End();
}

/*!
* @brief メイン処理
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