#pragma once

class Button {
public:
	Button() :push(0), pushDown(false), pushUp(false) {}
	~Button() = default;

	void Update(const bool keyPush);
	double GetPushStay()const { return pushUp ? 0.0 : push; }
	double GetPushOnPushUp()const { return push; }
	bool GetPushDown()const { return pushDown; }
	bool GetPushUp()const { return pushUp; }
private:
	double push;
	bool pushDown;
	bool pushUp;
};