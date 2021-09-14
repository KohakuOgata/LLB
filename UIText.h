#pragma once
#include "UIObject.h"

class Double2;
class Point2D;

class UIText :
    public UIObject
{
public:
    UIText(SceneBase* _scene);
    ~UIText();

    void Draw() override;

    void SetOffset(const Double2& _offset);
    void SetFontHandle(const int _fontHandle);
    void SetColor(const unsigned int _color);
    void SetText(const std::string& _string);

private:
    std::unique_ptr<Point2D> pos;
    std::unique_ptr<Double2> offset;
    int fontHandle;
    unsigned int color;
    std::string string;
};

