#pragma once

#include <memory>
#include <initializer_list>
#include <list>

enum class InputID;
class Button;

class VButton {
public:
	VButton();
	VButton(const std::initializer_list<InputID> _inputs);

	void Update();
	void AddInput(const InputID idToAdd);
	void AddInput(const std::initializer_list<InputID> idsToAdd);
	void EraseInput(const InputID idToErase);
	void EraseInput(const std::initializer_list<InputID> idsToErase);
	void ClearInput();

public:
	std::unique_ptr<Button> button;

private:
	std::list<InputID> inputs;
};