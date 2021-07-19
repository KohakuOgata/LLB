#pragma once

#include "InputID.h"

#include <DxLib.h>
#include <initializer_list>

class Double2;
class Point2D;

class Input {

	//メインの初期化で1度だけ呼ぶ
	friend void InputInit();

	//メインループで毎フレーム呼ぶ
	friend void InputUpdate();

private:
	Input() = default;
	~Input() = default;

	static void Init();
	
	static void Update();

public:
	//アナログスティックの無効範囲を設定する
	//アナログ取得時用（Double2で返ってくるやつ）
	//0.0 ～ 1.0を渡す
	static void SetJoypadStickDeadZoneAnalog (const double& left, const double& right, const int& inputType = DX_INPUT_PAD1);

	//アナログスティックの無効範囲を設定する
	//デジタル取得時用（GetPush系で取るやつ）
	//0.0 ～ 1.0を渡す
	static void SetJoypadStickDeadZoneDigital(const double& left, const double& right, const int& inputType = DX_INPUT_PAD1);

	//引数で指定されたボタンが連続して押されているフレーム数を返す
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> （パッド入力取得時に使用）
	static double GetPushStay(const InputID& inputID);

	//引数で指定されたボタンを押した瞬間だけ(true)を返す
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> （パッド入力取得時に使用）
	static bool GetPushDown(const InputID& inputID);

	//引数で指定されたボタンを離した瞬間だけ(true)を返す
	//inputID : InputID::<Key / Mouse / XInput>
	//inputType : DX_INPUT_PAD<1 ~ 16> （パッド入力取得時に使用）
	static bool GetPushUp(const InputID& inputID, unsigned int* const outPush = nullptr);

	//マウスカーソルの画面内座標をPoint2D型で返す
	static Point2D GetMousePos(void);

	//このフレームでのマウスホイールの回転量を返す
	static int GetMouseRot(void);
	
	//引数で指定されたすべてのボタンが同時に押された最初のフレームだけ(true)を返す
	static bool GetMultiplePushDown(const std::initializer_list<InputID> inputCodes);

	static double GetJoypadLeftTrigger(const int& inputType = DX_INPUT_PAD1);
	static double GetJoypadRightTrigger(const int& inputType = DX_INPUT_PAD1);
	static Double2 GetJoypadLeftStick(const int& inputType = DX_INPUT_PAD1);
	static Double2 GetJoypadRightStick(const int& inputType = DX_INPUT_PAD1);

	static void PrintJoypadAll(const int& inputType = DX_INPUT_PAD1);
};
