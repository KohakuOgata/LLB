#include "UIText.h"

#include <DxLib.h>

#include "Primitive2D.h"

UIText::UIText(SceneBase* _scene):
	UIObject(_scene),
	pos(std::make_unique<Point2D>()),
	offset(std::make_unique<Double2>()),
	fontHandle(-1),
	color(GetColor(0,0,0)),
	string()
{
}

UIText::~UIText()
{
}

void UIText::Draw()
{
	const int Width = GetDrawStringWidthToHandle(string.c_str(), strlen(string.c_str()), fontHandle);
	const int Height = GetFontSizeToHandle(fontHandle);
	const int DrawX = static_cast<int>(pos->x + Width * offset->x);
	const int DrawY = static_cast<int>(pos->y + Height * offset->y);
	DrawStringToHandle(DrawX, DrawY, string.c_str(), color, fontHandle);
}

void UIText::SetOffset(const Double2& _offset)
{
	*offset = _offset;
}

void UIText::SetFontHandle(const int newHandle)
{
	fontHandle = newHandle;
}

void UIText::SetColor(const unsigned int _color)
{
	color = _color;
}

void UIText::SetText(const std::string& newString)
{
	string = newString;
}
