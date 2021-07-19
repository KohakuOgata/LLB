#pragma once

#include "Primitive2D.h"

#include <list>

class Physics {
	friend void PhysicsesUpdate();
public:
	Physics(const Point2D& _pos = Point2D::Zero, const Vec2& _vel = Vec2::Zero, const Vec2& _acc = Vec2::Zero, const double& _resist = 0.0);
	Physics& operator =(const Physics& physics);
	~Physics();
	Physics(const Physics& physics);


	void Print() const;

private:
	void Update();

public:
	Point2D pos;
	Vec2 vel;
	Vec2 acc;
	double resist;

private:
	std::list<Physics*>::iterator it;

};