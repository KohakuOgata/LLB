#include "Ball.h"

#include "Stage.h"
#include "Player.h"
#include "Color.h"
#include "Timer.h"
#include "SceneBase.h"
#include "Define.h"
#include "Time.h"
#include "Utility.h"
#include "Camera.h"

#include <DxLib.h>

const double Ball::Radius = 20.0;
const double Ball::RespawnAnimTime = 1.0;
const double Ball::InitiationMoveSpeed = 1300.0;
const double Ball::PossessedTime = 2.0;
const double Ball::Gravity = 380.0 * 2 / Utility::Square(0.64);
const double Ball::ParriedInitialVel = 380 / 0.64 - 0.64 / 2 * Ball::Gravity;
const double Ball::ActualSpeedFactor = 135.0;
const double Ball::HitstopFactor = 0.01;

Ball::Ball(SceneBase* _pScene):
	GameObject(_pScene), 
	collider(std::make_unique<Circle2D>(InitialPos, Radius)),
	vel(std::make_unique<Vec2>(Vec2::Zero)),
	color(Define::ETeam::None),
	state(EState::Initiation),
	respawnAnimTimer(std::make_unique<Timer>(RespawnAnimTime)),
	isPossessed(false),
	InitialPos(Stage::GetStageCenter().x, 154),
	hitstopTimer(std::make_unique<Timer>(0)),
	swingedSamePlayerNum(0),
	lastSwingedPlayer(EPlayer::None),
	onCompleteBeingSwinged(false)
{
}

Ball::~Ball()
{
}

void Ball::Start()
{
	collider->p = InitialPos;
	*vel = Vec2::Zero;
	speed = initialSpeed;
	color = Define::ETeam::None;
	state = EState::Initiation;
	respawnAnimTimer->Start();
}

void Ball::Update()
{
	collider->p += *vel * Time::DeltaTime();

	switch (state)
	{
	case Ball::EState::Initiation:
		InitiationUpdate();
		break;
	case Ball::EState::Possessed:
		PossessdUpdate();
		break;
	case Ball::EState::Static:
		break;
	case Ball::EState::Banted:
		BantedUpdate();
		break;
	case Ball::EState::BeingSwinged:
		BeingSwingedUpdate();
		break;
	case Ball::EState::Swinged:
		SwingedUpdate();
		break;
	default:
		break;
	}
}

void Ball::Draw()
{

	const Point2D camPos = GetScene()->FindGameObject<Camera>()->GetFlame().LeftTop();
	{
		unsigned int outsideColor;
		switch (color)
		{
		case Define::ETeam::Red:
			outsideColor = ::Color::Get(ColorID::Red);
			break;
		case Define::ETeam::Blue:
			outsideColor = ::Color::Get(ColorID::Blue);
			break;
		case Define::ETeam::Yellow:
			outsideColor = ::Color::Get(ColorID::Yellow);
			break;
		case Define::ETeam::Green:
			outsideColor = ::Color::Get(ColorID::Green);
			break;
		default:
			outsideColor = ::Color::Get(ColorID::Magenta);
			break;
		}
		DrawCircle(collider->p.x - camPos.x, collider->p.y - camPos.y, static_cast<int>(Radius * 1.3), outsideColor);
	}
	DrawCircle(collider->p.x - camPos.x, collider->p.y - camPos.y, static_cast<int>(Radius), ::Color::Get(ColorID::Gray));
}

void Ball::DebugDraw()
{
	printfDx("Ball Speed : %d\n", speed);
}

void Ball::SetInitialSpeed(const double _initialSpeed)
{
	initialSpeed = _initialSpeed;
}

void Ball::Bant(const Define::EDirection direction)
{
	Vec2 initialVel(0.0, ParriedInitialVel);
	switch (direction)
	{
	case Define::EDirection::Up:
		initialVel.SetAngle(-Define::Pi / 2);
		break;
	default:
		break;
	}
	*vel = initialVel;
	state = EState::Banted;
}

bool Ball::Swing(Player& player, const double chargedRate)
{
	if (state == EState::Possessed && possessedPlayer->GetPlayerNo() != player.GetPlayerNo()) {
		player.OnParried();
		return false;
	}
	possessedPlayer = &player;
	SwingedInit(player, chargedRate);
	return true;
}

const Circle2D& Ball::GetCollider() const
{
	return *collider;
}

Cupsule2D Ball::GetSweepCollider() const
{
	return Cupsule2D(Segment2D(Point2D(collider->p - *vel * Time::DeltaTime()), collider->p), Radius);
}

bool Ball::IsOnCompleteBeingSwinged() const
{
	return onCompleteBeingSwinged;
}

int Ball::GetSpeed()
{
	return speed;
}

void Ball::ChangeState(const EState nextState)
{
	switch (nextState)
	{
	case EState::Static:
		StaticInit();
		return;
	default:
		break;
	}
	state = nextState;
}

void Ball::InitiationUpdate()
{
	if (respawnAnimTimer->IsActive() && !respawnAnimTimer->IsFinishing())
		return;
	Point2D moveGoal;
	if (respawnAnimTimer->IsFinishing()) {
		*vel = Vec2(0, InitiationMoveSpeed);
	}
	if (!isPossessed) {
		if (collider->p.y + InitiationMoveSpeed * Time::DeltaTime() > Stage::StageSize.y - Player::BallPossessHeight) {
			ChangeState(EState::Static);
		}
	}
	else {
		moveGoal = possessedPlayer->GetCollider().Center() + Vec2(Player::BallPossessWidth, -Player::BallPossessHeight);
		if ((moveGoal - collider->p).SqLength() < Utility::Square(InitiationMoveSpeed)) {
			StartPossessd(possessedPlayer);
			return;
		}
		*vel = Vec2(moveGoal - collider->p).SetLength(InitiationMoveSpeed);
	}
}

void Ball::StaticInit()
{
	*vel = Vec2::Zero;
	state = EState::Static;
}

void Ball::PossessdUpdate()
{
	if (!possessdTimer->IsFinishing()) {
		collider->p = possessedPlayer->GetBallPossessPos();
	}
	else {
		possessedPlayer->OnParried();
		Bant(Define::EDirection::Up);
	}
}

void Ball::BantedUpdate()
{
	vel->y += Gravity * Time::DeltaTime();
	collider->p += *vel * Time::DeltaTime();
	if (WallCollide()) {
		*vel = Vec2(0.0, GetActualSpeed());
	}
}

void Ball::SwingedInit(const Player& player, const double chargedRate)
{
	if (player.GetPlayerNo() != lastSwingedPlayer)
		swingedSamePlayerNum = 0;
	swingedSamePlayerNum += 1;
	if (chargedRate) {
		speed += (2.34 / (static_cast<double>(swingedSamePlayerNum) + 1.6) + 1.1) * chargedRate;
	}
	else {
		speed += 1;
	}
	hitstopTimer->SetMaxTime(speed * HitstopFactor);
	hitstopTimer->Start();
	*vel *= 0.0;
	color = player.GetTeam();
	state = EState::BeingSwinged;
}

void Ball::BeingSwingedUpdate()
{
	onCompleteBeingSwinged = false;
	if (hitstopTimer->IsFinishing()) {
		*vel = possessedPlayer->GetBallDegree() * GetActualSpeed();
		state = EState::Swinged;
		onCompleteBeingSwinged = true;
		possessedPlayer = nullptr;
		isPossessed = false;
	}
}

void Ball::SwingedUpdate()
{
	const auto& stage = GetScene()->FindGameObject<Stage>()->GetCollider();
	if (collider->p.x < stage.Left() + Radius) {
		collider->p.x = stage.Left() + Radius;
		vel->x *= -1;
	}
	else if (collider->p.x > stage.Right() - Radius) {
		collider->p.x > stage.Right() - Radius;
		vel->x *= -1;
	}
	if (collider->p.y < stage.Top() + Radius) {
		collider->p.y = stage.Top() + Radius;
		vel->y *= -1;
	}
	else if (collider->p.y > stage.Bottom() - Radius) {
		collider->p.y > stage.Bottom() - Radius;
		vel->y *= -1;
	}
	for (auto& player : GetScene()->FindGameObjects<Player>()) {
		if (color != player->GetTeam() && GetSweepCollider().IsCollided(player->GetCollider())) {

		}
	}
}

void Ball::StartPossessd(Player* _possessdPlayer)
{
	possessedPlayer = _possessdPlayer;
	possessdTimer->Start();
	state = EState::Possessed;
}

bool Ball::WallCollide()
{
	const auto& stage = GetScene()->FindGameObject<Stage>()->GetCollider();
	bool isCollided = false;
	if (collider->p.x < stage.Left() + Radius) {
		collider->p.x = stage.Left() + Radius;
		isCollided = true;
	}
	else if (collider->p.x > stage.Right() - Radius) {
		collider->p.x > stage.Right() - Radius;
		isCollided = true;
	}
	if (collider->p.y < stage.Top() + Radius) {
		collider->p.y = stage.Top() + Radius;
		isCollided = true;
	}
	else if (collider->p.y > stage.Bottom() - Radius) {
		collider->p.y > stage.Bottom() - Radius;
		isCollided = true;
	}
	return isCollided;
}

double Ball::GetActualSpeed() const
{
	return speed * ActualSpeedFactor;
}
