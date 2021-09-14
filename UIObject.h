#pragma once
#include "GameObject.h"

#include <memory>

class AABB2D;

class UIObject :
    public GameObject
{
public:
    UIObject(SceneBase* _scene);
    ~UIObject();
    
    void Update() override {};
    void Draw() override {};

private:
    std::shared_ptr<UIObject> parent;
};

