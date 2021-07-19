#include "TestScene.h"

#include "Primitive2D.h"
#include "Config.h"
#include "Define.h"
#include "Input.h"
#include "IOnSceneChangedListener.h"
#include "VInput.h"
#include "Time.h"
#include "Parameter.h"
#include "SceneID.h"
#include "Timer.h"
#include "Liner4TreeMgr.h"
#include "Utility.h"

#include <vector>

namespace {

	enum ShapeName {
		Circle,
		Segment,
		Cupsule,
		Polygon
	};

	int selectingShape = ShapeName::Circle;
	int shapingFase = 0;
	std::vector<Point2D> points;
	int VelMax = 50;
	int VelMin = 40;
	bool mode = true;
	const int SpawnInterval = 0;
	int spawnTimer = 0;
	double momentum = 0;
	double ReflectionRate = 1.0;
	double gravityScale = 0.5;
	Point2D mousePosBuf;
	const int InitialColliderNum = 1000;
	bool flameDraw = false;
	bool b = false;
}

const double CollideCircle::RadiusMin = 2;
const double CollideCircle::RadiusMax = 2;
const double CollideCircle::MassFactor = 1.0;
const double CollideCircle::VelMin = 0;
const double CollideCircle::VelMax = 0;

const int InfectionCircle::MaxInfectedTime = 300;

Vec2 GravitalCircle::Gravity = Vec2(0.0, 100.0);
AABB2D GravitalCircle::flame = AABB2D();
Vec2 GravitalCircle::flameVec = 0.0;

TestScene::TestScene(IOnSceneChangedListener* _impl, const Parameter& _parameter)
	:SceneBase(_impl, _parameter), tree(new Liner4TreeMgr<CollideCircle>(6, AABB2D(/*Config::WindowSize*/AABB2D(Point2D(300, 200), Point2D(Config::WindowSize - Point2D(300, 200))))))
{
	GravitalCircle::flame = tree->flame;
	GravitalCircle::Gravity = Vec2(0.0, 100.0);
	for (int i = 0; i < InitialColliderNum; i++) {
		const double r = Utility::RandomFloatD();
		const double SizeAlpha = r * r ;
		circles.push_back(new GravitalCircle(Point2D(/*Config::WindowCenter + Vec2(2.0 * Define::Pi * Utility::RandomFloatD()) * Utility::Lerp(0.0, 250.0, 1.0 - SizeAlpha)*/Utility::Lerp(GravitalCircle::flame.Left(), GravitalCircle::flame.Right(), Utility::RandomFloatD()), Utility::Lerp(GravitalCircle::flame.Top(), GravitalCircle::flame.Bottom(), Utility::RandomFloatD())), Utility::RandomFloatD() * Utility::RandomFloatD()));
		tree->CreateCollider(*circles.back(), *circles.back()->collider);
	}
}

TestScene::~TestScene()
{
	for (auto& it : circles) {
		if (it) {
			delete it;
			it = nullptr;
		}
	}
	circles.clear();
	delete tree;
	tree = nullptr;
	for (auto& shape : shapes) {
		delete shape;
		shape = nullptr;
	}
	shapes.clear();

}

void TestScene::Update()
{
	if (Input::GetPushDown(InputID::KeyEscape))
		GoTestScene();
	TestUpdate();
}

void TestScene::Draw()
{
	ConstPrint();
	TestDraw();
}

void TestScene::GoTestScene()
{
	PopScene();
}

void TestScene::ConstPrint() const
{
	printfDx("TestScene\n");
	printfDx("Press G + T or Press Esc to Back\n");

	printfDx("\n");
}

void TestScene::TestUpdate()
{
	if (mode) {
		/*if (spawnTimer) {
			spawnTimer -= 1;
		}
		else if (Input::GetPushStay(InputID::MouseLeft)) {
			circles.push_back(new CollideCircle(Input::GetMousePos()));
			tree->CreateCollider(*circles.back(), *circles.back()->collider);
			spawnTimer = SpawnInterval;
		}*/
		/*if (Input::GetPushStay(InputID::MouseLeft)) {
			GravitalCircle::flameVec = Input::GetMousePos() - mousePosBuf;
			tree->flame += GravitalCircle::flameVec;
		}
		else {
			GravitalCircle::flameVec = Vec2::Zero;
		}*/
		if (Input::GetPushStay(InputID::MouseLeft)) {
			Circle2D(Input::GetMousePos(), CollideCircle::RadiusMax).Draw(Color::Get(ColorID::Red), true);
		}
		else if(Input::GetPushUp(InputID::MouseLeft)){
			circles.push_back(new InfectionCircle(Input::GetMousePos(), 100.0, true));
			tree->CreateCollider(*circles.back(), *circles.back()->collider);
			*circles.back()->vel *= 10.0;
		}
		mousePosBuf = Input::GetMousePos();
		GravitalCircle::flame = tree->flame;
		if (Input::GetPushStay(InputID::MouseRight)) {
			if (Input::GetMouseRot() > 0) {
				gravityScale *= 1.1;
			}
			else if (Input::GetMouseRot() < 0) {
				gravityScale /= 1.1;
			}
			GravitalCircle::Gravity = (Input::GetMousePos() - tree->flame.Center()) * gravityScale;
		}
		else {
			if (Input::GetMouseRot() > 0) {
				GravitalCircle::Gravity *= 1.1;
			}
			else if (Input::GetMouseRot() < 0) {
				GravitalCircle::Gravity /= 1.1;
			}
		}
		if (Input::GetPushUp(InputID::MouseRight)) {
			GravitalCircle::Gravity = Vec2(0.0, 100.0);
		}
		momentum = 0.0;
		for (auto& it : circles) {
			it->Update();
			momentum += it->mass * it->vel->Length();
		}
		tree->Update();
		for (auto& it : tree->collideList) {
			if (it.c1->object.collider->IsCollided(it.c2->object.collider)) {
				it.c1->object.isCollided = it.c2->object.isCollided = true;
				Circle2D& c1 = *it.c1->object.collider;
				Circle2D& c2 = *it.c2->object.collider;
				const Vec2 P1ToP2 = c2.p - c1.p;
				const Vec2 P1ToP2Norm = P1ToP2.GetNormalized();
				const double DecollisionDis = (c1.r + c2.r - P1ToP2.Length()) / 2;
				c1.p -= P1ToP2Norm * DecollisionDis;
				c2.p += P1ToP2Norm * DecollisionDis;
				Vec2& v1 = *it.c1->object.vel;
				Vec2& v2 = *it.c2->object.vel;
				const Vec2 V1ToC2 = P1ToP2Norm * v1.Dot(P1ToP2Norm);
				const Vec2 V2ToC1 = -P1ToP2Norm * v2.Dot(-P1ToP2Norm);
				const double M1 = it.c1->object.mass;
				const double M2 = it.c2->object.mass;
				const double OldMomentum = M1 * v1.Length() + M2 * v2.Length();
				const Vec2 newV1 = (v1 - V1ToC2) + (v1 * (M1 - M2) + v2 * 2 * M2) / (M1 + M2);
				const Vec2 newV2 = (v2 - V2ToC1) + (v2 * (M2 - M1) + v1 * 2 * M1) / (M1 + M2);
				const double MomentumRate = OldMomentum / (M1 * newV1.Length() + M2 * newV2.Length());
				v1 = newV1 * MomentumRate;
				v2 = newV2 * MomentumRate;

				/*if (it.c1->object.infectedTimer > 0 && !it.c2->object.infectedTimer) {
					it.c2->object.infectedTimer = 1;
				}
				else  if (it.c2->object.infectedTimer > 0 && !it.c1->object.infectedTimer) {
					it.c1->object.infectedTimer = 1;
				}*/
			}
		}
	}	
}

void TestScene::TestDraw() const
{
	if (mode) {
		if (Input::GetMultiplePushDown({ InputID::Key0, InputID::Pad1A })) {
			b = !b;
		}
		Circle2D(Point2D(100, 100), 50).Draw(b ? Color::Get(ColorID::Red) : Color::Get(ColorID::Black));
		tree->Draw();
		printfDx("\n");
		Input::PrintJoypadAll();
		Input::PrintJoypadAll(DX_INPUT_PAD2);
		printfDx("Total Momentum : %.0lf\n", momentum);
		printfDx("Gravity : %.0lf\n", GravitalCircle::Gravity.Length());
		if (flameDraw)
			tree->flame.Draw(GetColor(230, 230, 230), false, 3);
		if (Input::GetPushStay(InputID::KeyA)) {
			const unsigned int gray = Color::Get(ColorID::Gray);
			for (int i = 0; i < circles.size() - 1; i++) {
				for (int i2 = i + 1; i2 < circles.size(); i2++) {
					Segment2D(circles.at(i)->collider->p, circles.at(i2)->collider->p).Draw(gray);
				}
			}
		}
		if (Input::GetPushStay(InputID::KeyS)) {
			const unsigned int green = Color::Get(ColorID::Green);
			for (const auto it : tree->collideList) {
				Segment2D(it.c1->object.collider->p, it.c2->object.collider->p).Draw(green);
			}
		}
		if (Input::GetPushStay(InputID::MouseRight)) {
			Segment2D(Input::GetMousePos(), tree->flame.Center()).Draw(GetColor(177, 0, 182), false, 5);
		}
		for (const auto& it : circles)
			it->Draw();
	}
}

MovingShape::MovingShape(Primitive2D* _shape) :
	shape(_shape), vel(new Vec2(Vec2(Define::Pi * 2 * (double)(GetRand(100)) / 100.0)* Utility::Lerp(VelMin, VelMax, (double)(GetRand(100)) / 100.0)))
{
}

MovingShape::~MovingShape()
{
	if (vel != nullptr) {
		delete vel;
		vel = nullptr;
	}
	if (shape != nullptr) {
		delete shape;
		shape = nullptr;
	}
}

void MovingShape::Update()
{
	shape->GetP() += *vel * Time::DeltaTime();
	const AABB2D aabb = shape->GetAABB2D();
	if (aabb.Left() < 0.0) {
		shape->GetP().x -= aabb.Left() - 1;
		vel->x *= -1;
	}
	else if (aabb.Right() > Config::WindowSize.x) {
		shape->GetP().x -= aabb.Right() - Config::WindowSize.x + 1;
		vel->x *= -1;
	}
	if (aabb.Top() < 0.0) {
		shape->GetP().y -= aabb.Top() - 1;
		vel->y *= -1;
	}
	else if (aabb.Bottom() > Config::WindowSize.y) {
		shape->GetP().y -= aabb.Bottom() - Config::WindowSize.y + 1;
		vel->y *= -1;
	}
}

void MovingShape::Draw() const
{
	shape->Draw(Color::Get(ColorID::Black));
	shape->GetP().Draw(Color::Get(ColorID::Black));
}

CollideCircle::CollideCircle(const Point2D& _p, const double& sizeAlpha) :
	collider(new Circle2D(_p, Utility::Lerp(RadiusMin, RadiusMax, sizeAlpha))),
	vel(new Vec2(Vec2(Utility::RandomFloatD()* Define::Pi * 2)* Utility::Lerp(VelMin, VelMax, Utility::RandomFloatD()))),
	mass(collider->r* collider->r* collider->r* MassFactor),
	isCollided(false)
{
}

CollideCircle::~CollideCircle()
{
	if (collider != nullptr) {
		delete collider;
		collider = nullptr;
	}
	if (vel != nullptr) {
		delete vel;
		vel = nullptr;
	}
}

void CollideCircle::Update()
{
	collider->p += *vel * Time::DeltaTime();
	const AABB2D aabb = collider->GetAABB2D();
	if (aabb.Top() <= 0) {
		collider->p.y -= aabb.Top();
		vel->y *= -1.0;
	}
	else if (aabb.Bottom() >= Config::WindowSize.y) {
		collider->p.y -= aabb.Bottom() - Config::WindowSize.y;
		vel->y *= -1.0;
	}
	if (aabb.Left() <= 0) {
		collider->p.x -= aabb.Left();
		vel->x *= -1.0;
	}
	else if (aabb.Right() >= Config::WindowSize.x) {
		collider->p.x -= aabb.Right() - Config::WindowSize.x;
		vel->x *= -1.0;
	}
	isCollided = false;
}

void CollideCircle::Draw() const
{
	collider->Draw(isCollided ? GetColor(10, 248, 10) : GetColor(48, 209, 255), true);
}

GravitalCircle::GravitalCircle(const Point2D& _p, const double& sizeAlpha) :
	CollideCircle(_p, sizeAlpha)
{
}

GravitalCircle::~GravitalCircle()
{
}

void GravitalCircle::Update()
{
	isCollided = false;
	*vel += Gravity * Time::DeltaTime();
	collider->p += *vel * Time::DeltaTime();

	const AABB2D aabb = collider->GetAABB2D();
	if (aabb.Left() <= flame.Left()) {
		collider->p.x += flame.Left() - aabb.Left();
		vel->x = -vel->x + 2 * flameVec.x;
	}
	else if (aabb.Right() >= flame.Right()) {
		collider->p.x -= aabb.Right() - flame.Right();
		/*vel->x *= -1.0;
		vel->x += flameVec.x;*/
		vel->x = -vel->x + 2 * flameVec.x;
	}
	if (aabb.Top() <= flame.Top()) {
		//const double OldY = collider->p.y;
		collider->p.y += flame.Top() - aabb.Top();
		/*Vec2 newVel = *vel;
		newVel.y *= -1.0;
		newVel.y += flameVec.y;
		*vel = newVel;*/
		vel->y = -vel->y + 2 * flameVec.y;
		/*const double SqVel = vel->SqLength();
		const double SqNewVel = newVel.SqLength();
		*vel = newVel * sqrt((SqNewVel + 2 * sqrt(SqNewVel * SqVel) + SqVel) + 2 * Gravity * (collider->p.y - OldY) / SqNewVel);*/
	}
	else if (aabb.Bottom() >= flame.Bottom()) {
		//const double OldY = collider->p.y;
		collider->p.y -= aabb.Bottom() - flame.Bottom();
		/*Vec2 newVel = *vel;
		newVel.y *= -1.0;
		newVel.y += flameVec.y;
		*vel = newVel;*/
		vel->y = -vel->y + 2 * flameVec.y;
		/*const double SqVel = vel->SqLength();
		const double SqNewVel = newVel.SqLength();
		*vel = newVel * sqrt((SqNewVel + 2 * sqrt(SqNewVel * SqVel) + SqVel) + 2 * Gravity * (collider->p.y - OldY) / SqNewVel);*/
	}
}

InfectionCircle::InfectionCircle(const Point2D& _p, const double& sizeAlpha, const bool _infected) :
	GravitalCircle(_p, sizeAlpha), infectedTimer(_infected ? 1 : 0)
{
}

InfectionCircle::~InfectionCircle()
{
}

void InfectionCircle::Update()
{
	GravitalCircle::Update();
	if (infectedTimer > MaxInfectedTime)
		infectedTimer = -1;
	if (infectedTimer > 0)
		infectedTimer += 1;
}

void InfectionCircle::Draw() const
{
	if (!infectedTimer)
		collider->Draw(Color::Get(ColorID::Cyan), true);
	else if (infectedTimer > 0)
		collider->Draw(GetColor(255, 254 * Utility::Map((double)(infectedTimer), 1.0, (double)(MaxInfectedTime)), 0), true);
	else
		collider->Draw(Color::Get(ColorID::Yellow), true);
}
