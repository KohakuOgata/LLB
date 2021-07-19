#pragma once

enum class SceneID;
class Parameter;

class IOnSceneChangedListener
{
public:
    IOnSceneChangedListener() = default;
    virtual ~IOnSceneChangedListener() = default;
    virtual void OnSceneChanged(const SceneID scene, const Parameter parameter, const bool stackClear) = 0;
    virtual void OnScenePop() = 0;
};