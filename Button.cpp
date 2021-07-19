#include "Button.h"

#include <limits>
#include "Time.h"

void Button::Update(const bool keyPush)
{
	if (pushUp)
		push = 0;
	if (keyPush) {
		pushDown = (push == 0);
		pushUp = false;
		if (std::numeric_limits<double>::max() - push > Time::DeltaTime())
			push += Time::DeltaTime();
	}
	else {
		pushUp = push;
		pushDown = false;
	}
}