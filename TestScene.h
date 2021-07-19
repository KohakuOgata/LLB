#pragma once

#include "SceneBase.h"

#include <memory>
#include <vector>

class IOnSceneChangeListener;
class Parameter;
class Timer;
class Primitive2D;
template<typename T>
class Liner4TreeMgr;
class Vec2;
class Circle2D;
class Point2D;
class AABB2D;

class MovingShape {
public:
	MovingShape(Primitive2D* _shape);
	~MovingShape();

	void Update();
	void Draw() const;

	Primitive2D* shape;
	Vec2* vel;
};

class CollideCircle {
public:
	CollideCircle(const Point2D& _p, const double& sizeAlpha);
	~CollideCircle();

	virtual void Update();
	virtual void Draw() const;

	Circle2D* collider;
	Vec2* vel;
	double mass;
	bool isCollided;

	static const double RadiusMin;
	static const double RadiusMax;
	static const double MassFactor;
	static const double VelMin;
	static const double VelMax;
};

class GravitalCircle : 
	public CollideCircle {
public:
	GravitalCircle(const Point2D& _p, const double& sizeAlpha);
	~GravitalCircle();

	void Update() override;

	static Vec2 Gravity;
	static AABB2D flame;
	static Vec2 flameVec;
};

class InfectionCircle :
	public GravitalCircle {
public:
	InfectionCircle(const Point2D& _p, const double& sizeAlpha, const bool _infected);
	~InfectionCircle();

	void Update() override;
	void Draw() const override;

	//0:ñ¢ä¥êı, ê≥:ä¥êı, -1:ñ∆âu
	int infectedTimer;
	static const int MaxInfectedTime;
};

class TestScene : public SceneBase {
public:
	TestScene(IOnSceneChangedListener* _impl, const Parameter& parameter);
	~TestScene();

	void Update() override;
	void Draw() override;

	void GoTestScene() override;
private:
	void ConstPrint() const;
	void TestUpdate();
	void TestDraw() const;

public:

private:
	std::vector<MovingShape*> shapes;
	std::vector<CollideCircle*> circles;
	Liner4TreeMgr<CollideCircle>* tree;
};