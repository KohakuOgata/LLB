#include "Physics.h"

#include <DxLib.h>

namespace {
	std::list<Physics*> physicses;
}

void PhysicsesUpdate()
{
	for (auto& it : physicses)
		it->Update();
}

Physics::Physics(const Point2D& _pos, const Vec2& _vel, const Vec2& _acc, const double& _resist)
	: pos(_pos), vel(_vel), acc(_acc), resist(_resist)
{
	physicses.push_back(this);
	it = --physicses.end();
}

Physics::Physics(const Physics& physics)
{
	pos    = physics.pos;
	vel    = physics.vel;
	acc    = physics.acc;
	resist = physics.resist;
	physicses.push_back(this);
	it = --physicses.end();
}

Physics::~Physics()
{
	physicses.erase(it);
}

Physics& Physics::operator=(const Physics& physics)
{
	pos = physics.pos;
	vel = physics.vel;
	acc = physics.acc;
	resist = physics.resist;
	return *this;
}

void Physics::Print() const
{
	printfDx("pos x : %-5.0f, y : %-5.0f\nvel x : %-5.2f, y : %-5.2f\nacc x : %-5.2f, y : %-5.2f\n\n",
		pos.x, pos.y, vel.x, vel.y, acc.x, acc.y);
}

void Physics::Update()
{
	acc -= vel * resist;
	vel += acc;
	pos += vel;
}
