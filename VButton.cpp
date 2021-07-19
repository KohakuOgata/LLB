#include "VButton.h"

#include "Input.h"
#include "Button.h"

VButton::VButton()
	:button(std::make_unique<Button>()), inputs()
{
}

VButton::VButton(const std::initializer_list<InputID> _inputs)
	:button(std::make_unique<Button>()), inputs(_inputs)
{
}

void VButton::Update()
{
	bool anyButtonPush = false;
	for (auto it : inputs) {
		anyButtonPush = Input::GetPushStay(it);
		if (anyButtonPush)
			break;
	}
	button->Update(anyButtonPush);	//設定されたキーの論理和でアップデート
}

void VButton::AddInput(const InputID idToAdd)
{
	for (const auto& existingID : inputs)
		if (existingID == idToAdd)
			return;
	inputs.push_back(idToAdd);
}

void VButton::AddInput(const std::initializer_list<InputID> idsToAdd)
{
	for (const auto& newID : idsToAdd) {
		for (const auto& existingID : inputs)
			if (existingID == newID)
				return;
		inputs.push_back(newID);
	}
}

void VButton::EraseInput(const InputID idToErase)
{
	inputs.erase(std::find(inputs.begin(), inputs.end(), idToErase));
}

void VButton::EraseInput(const std::initializer_list<InputID> idsToErase)
{
	for (const auto& idToDelete : idsToErase)
		inputs.remove(idToDelete);
}

void VButton::ClearInput()
{
	inputs.clear();
}
