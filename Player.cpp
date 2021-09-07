#include "Player.h"

#include "Primitive2D.h"
#include "Stage.h"
#include "SceneBase.h"
#include "GameManager.h"
#include "Input.h"
#include "Time.h"
#include "Timer.h"
#include "Camera.h"
#include "DebugMode.h"
#include "Ball.h"

#include <assert.h>
#include <DxLib.h>
#include <string>

int Player::playerNum = 0;
const Double2 Player::ColliderSize = Double2(80, 185);
const Double2 Player::SwingColliderSize = Double2(145, Player::ColliderSize.y);
const double Player::CrouchingColliderHeight = 125;
const double Player::SpeedHorizontal = 857;
const double Player::SpeedOnWall = 180;
const double Player::Gravity = 9500 * 0.7;
const double Player::WeakGravity = Player::Gravity * 0.7;
const double Player::JumpVelocity = -2760 * 0.7;
const double Player::AirJumpVelocity = Player::JumpVelocity * 0.7;
const double Player::BallPossessHeight = 135;
const double Player::BallPossessWidth = ColliderSize.x + 2 * Ball::Radius;
const double Player::ImmidiatelySwingTime = 24.0 / 60.0;
const double Player::MaxChargeTime = 20.0 / 60.0;
const double Player::SmashTime = 18.0 / 60.0;
const Vec2 Player::UpSwingDegree = Vec2(-Define::Pi / 3.0);
const Vec2 Player::GroundDownSwingDegree = Vec2(Define::Pi / 6.0);
const Vec2 Player::AirDownSwingDegree = Vec2(42.0 / 180.0 * Define::Pi);
const Vec2 Player::ForwardSpikeDegree = Vec2(83.0 / 180.0 * Define::Pi);
const Vec2 Player::BackweardSpikeDegree = Vec2(97.0 / 180.0 * Define::Pi);
const double Player::SwingAfterRigor = 8.0 / 60.0;
const double Player::InvincibleTime = 1.0;

namespace {
	const int ControllerMask[4] = {
		0x3000,
		0x4000,
		0x5000,
		0x6000
	};
	const InputID InputIDsController[] = {
		InputID::PadLeftThumbTiltUp,
		InputID::PadLeftThumbTiltDown,
		InputID::PadLeftThumbTiltLeft,
		InputID::PadLeftThumbTiltRight,
		InputID::PadA,
		InputID::PadX,
		InputID::PadB,
		InputID::PadY,
		InputID::PadRightThumbClick,
		InputID::PadRightThumbTiltUp,
		InputID::PadRightThumbTiltDown,
		InputID::PadRightThumbTiltLeft,
		InputID::PadRightThumbTiltRight,
		InputID::PadBack
	};
	const InputID InputIDsKeyboard[] = {
		InputID::KeyW,
		InputID::KeyS,
		InputID::KeyA,
		InputID::KeyD,
		InputID::KeyX,
		InputID::KeyZ,
		InputID::KeyC,
		InputID::KeyV,
		InputID::KeyF,
		InputID::KeyUp,
		InputID::KeyDown,
		InputID::KeyLeft,
		InputID::KeyRight,
		InputID::KeyEscape
	};
	const double RunAnimRoop = 0.53;
	const double SlowAnimThreshold = 300;
	double cameraX;
	double cameraY;
	double centerX;
	double centerY;
}

Player::Player(SceneBase* _pScene) :
	GameObject(_pScene),
	playerNo(playerNum++),
	stock(GetScene()->FindGameObject<GameManager>()->GetPlayerMaxStock()),
	life(GetScene()->FindGameObject<GameManager>()->GetPlayerMaxLife()),
	special(GetScene()->FindGameObject<GameManager>()->GetPlayerMaxSpecial()),
	isLive(false),
	isFacingLeft(false),
	state(EState::Neutral),
	velocity(std::make_unique<Vec2>(Vec2::Zero)),
	acceleration(std::make_unique<Vec2>(Vec2::Zero)),
	collider(std::make_unique<AABB2D>(ColliderSize)),
	swingCollider(std::make_unique<AABB2D>(SwingColliderSize)),
	isOnWall(false),
	isOnLand(false),
	isRubbingWall(false),
	canAirJump(true),
	isHorionalJump(false),
	isCrouching(false),
	animationTimer(std::make_unique<Timer>(1.0)),
	wallJumpTimer(std::make_unique<Timer>(0.1)),
	isSwinging(false),
	isSmashing(false),
	nonChargeSwingTimer(std::make_unique<Timer>(ImmidiatelySwingTime)),
	chargeTimer(std::make_unique<Timer>(MaxChargeTime)),
	swingDirection(Define::EDirection::None),
	swingAfterRigorTimer(std::make_unique<Timer>(SwingAfterRigor)),
	isGettingDamage(false)
{
	assert(playerNo >= 0 && playerNo <= 3);
	StateInit.push_back(&Player::NeutralInit);
	StateInit.push_back(&Player::CrouchInit);
	StateInit.push_back(&Player::RubWallInit);
	StateInit.push_back(&Player::SwingReadyInit);
	StateInit.push_back(&Player::SwingChargeInit);
	StateInit.push_back(&Player::SwingAfterInit);
	StateInit.push_back(&Player::SmashReadyInit);
	StateInit.push_back(&Player::SmashInit);
	StateInit.push_back(&Player::HitStopInit);
	StateInit.push_back(&Player::DamagedInit);

	StateUpdate.push_back(&Player::NeutralUpdate);
	StateUpdate.push_back(&Player::CrouchUpdate);
	StateUpdate.push_back(&Player::RubWallUpdate);
	StateUpdate.push_back(&Player::SwingReadyUpdate);
	StateUpdate.push_back(&Player::SwingChargeUpdate);
	StateUpdate.push_back(&Player::SwingAfterUpdate);
	StateUpdate.push_back(&Player::SmashReadyUpdate);
	StateUpdate.push_back(&Player::SmashUpdate);
	StateUpdate.push_back(&Player::HitStopUpdate);
	StateUpdate.push_back(&Player::DamagedUpdate);

	StateDraw.push_back(&Player::NeutralDraw);
	StateDraw.push_back(&Player::CrouchDraw);
	StateDraw.push_back(&Player::RubWallDraw);
	StateDraw.push_back(&Player::SwingReadyDraw);
	StateDraw.push_back(&Player::SwingChargeDraw);
	StateDraw.push_back(&Player::SwingAfterDraw);
	StateDraw.push_back(&Player::SmashReadyDraw);
	StateDraw.push_back(&Player::SmashDraw);
	StateDraw.push_back(&Player::HitStopDraw);
	StateDraw.push_back(&Player::DamagedDraw);
}

Player::~Player()
{
	playerNum -= 1;
}

void Player::Start()
{
	//•œŠˆ
	if (!(!isLive && stock))
		return;
	life = GetScene()->FindGameObject<GameManager>()->GetPlayerMaxLife();
	isLive = true;
	const double StageWidth = Stage::StageSize.x;
	const int PlayerNum = GetScene()->FindGameObjects<Player>().size();
	if (PlayerNum <= 2) {
		collider->Center({ StageWidth / 4 * (playerNo ? 3 : 1), collider->Size().y });
	}
	else {
		collider->Center({ StageWidth / 5 * (playerNo + 1), collider->Size().y });
	}
}

void Player::Update()
{
	if (isGettingDamage) {
		return;
	}
	(this->*StateUpdate.at(state))();
	PositionUpdate();
	WallCollideUpdate();
}

void Player::Draw()
{
	centerX = collider->Center().x;
	centerY = collider->Center().y;
	const Double2 camPos = GetScene()->FindGameObject<Camera>()->GetFlame().LeftTop();
	cameraX = camPos.x;
	cameraY = camPos.y;
	(this->*StateDraw.at(state))();
}

void Player::DebugDraw()
{
	DrawBox(collider->LeftTop().x - cameraX, collider->LeftTop().y - cameraY, collider->RightBottom().x - cameraX, collider->RightBottom().y - cameraY, Color::Get(ColorID::Black), false);
	printfDx("Any Move Input : %s\n", IsGettingAnyMoveInput() ? "true" : "false");
}

void Player::SetController(const Define::EController _controller)
{
	controller = _controller;
}

void Player::SetTeam(const Define::ETeam _team)
{
	team = _team;
	imageHandles = std::make_unique<ImageHandles>(team - 1);
}

Point2D Player::GetBallPossessPos() const
{
	return Point2D(collider->Center().x + (isFacingLeft ? -1 : 1) * (collider->Size().x + Ball::Radius + 1), collider->Bottom() - BallPossessHeight);
}

double Player::GetPushStay(const EAction action) const
{
	const int IntAction = static_cast<int>(action);
	if (controller == Define::EController::Keyboard)
		return Input::GetPushStay(InputIDsKeyboard[IntAction]);
	return Input::GetPushStay((InputID)((0x0fff & (int)InputIDsController[IntAction]) | ControllerMask[(int)controller]));
}

bool Player::GetPushDown(const EAction action) const
{
	const int IntAction = static_cast<int>(action);
	if (controller == Define::EController::Keyboard)
		return Input::GetPushDown(InputIDsKeyboard[IntAction]);
	return Input::GetPushDown((InputID)((0x0fff & (int)InputIDsController[IntAction]) | ControllerMask[(int)controller]));
}

bool Player::GetPushUp(const EAction action) const
{
	const int IntAction = static_cast<int>(action);
	if (controller == Define::EController::Keyboard)
		return Input::GetPushUp(InputIDsKeyboard[IntAction]);
	return Input::GetPushUp((InputID)((0x0fff & (int)InputIDsController[IntAction]) | ControllerMask[(int)controller]));
}

void Player::VelocityUpdate()
{
	if (isRubbingWall) {
		velocity->y = SpeedOnWall;
	}
	else {
		velocity->y += (GetPushStay(EAction::Jump) ? WeakGravity : Gravity) * Time::DeltaTime();
	}
	if (GetPushStay(EAction::Jump)) {
		if (isOnLand) {
			velocity->y = JumpVelocity;
			isHorionalJump = velocity->x;
			animationTimer->Stop();
			isOnLand = false;
		}
		else if (GetPushDown(EAction::Jump)) {
			if (isRubbingWall) {
				velocity->SetLength(JumpVelocity);
				velocity->SetAngle(isFacingLeft ? -Define::Pi * 3.0 / 4.0 : (-Define::Pi / 4.0));
			}
			else if (canAirJump) {
				velocity->y = AirJumpVelocity;
				canAirJump = false;
				animationTimer->Stop();
				animationTimer->SetMaxTime(0.6);
				animationTimer->Start();
			}
		}
	}
	if (((bool)GetPushStay(EAction::Left) ^ (bool)GetPushStay(EAction::Right)) && !isCrouching) {
		if (!wallJumpTimer->IsActive()) {
			if (GetPushStay(EAction::Left)) {
				if (isOnLand) {
					velocity->x = -SpeedHorizontal;
					isFacingLeft = true;
				}
				else {
					velocity->x += -SpeedHorizontal * 0.1;
					if (velocity->x < -SpeedHorizontal)
						velocity->x = -SpeedHorizontal;
				}
			}
			else if (GetPushStay(EAction::Right)) {

				if (isOnLand) {
					isFacingLeft = false;
					velocity->x = SpeedHorizontal;
				}
				else {
					velocity->x += SpeedHorizontal * 0.1;
					if (velocity->x > SpeedHorizontal)
						velocity->x = SpeedHorizontal;
				}
			}
		}
		if (isOnLand && (!animationTimer->IsActive() || animationTimer->Max() != RunAnimRoop)) {
			animationTimer->Stop();
			animationTimer->SetMaxTime(RunAnimRoop);
			animationTimer->Start(true);
		}
	}
	else {
		if (isOnLand) {
			if (GetPushStay(EAction::Down))
				velocity->x *= 0.9;
			else
				velocity->x = 0;
		}
		else {
			velocity->x *= 0.9;
		}
		if (animationTimer->IsActive() && animationTimer->Max() == RunAnimRoop)
			animationTimer->Stop();
	}
}

void Player::PositionUpdate()
{
	*collider += *velocity * Time::DeltaTime();
	if (isFacingLeft)
		swingCollider->RightBottom(collider->LeftBottom(), false);
	else
		swingCollider->LeftBottom(collider->RightBottom(), false);
}

void Player::WallCollideUpdate()
{
	isOnLand = false;
	isOnWall = false;
	if (collider->LeftTop().y < 0) {
		*collider = Point2D(collider->LeftTop().x, 0);
	}
	else if (collider->RightBottom().y > Define::StageHeight) {
		collider->Bottom(Define::StageHeight, false);
		//*collider = Point2D(collider->LeftTop().x, Define::StageHeight - ColliderSize.y);
		velocity->y = 0;
		isOnLand = true;
		canAirJump = true;
	}
	if (collider->LeftTop().x < 0) {
		*collider = Point2D(0.0, collider->LeftTop().y);
		velocity->x = 0;
		isOnWall = true;
		if (!isOnLand)
			isFacingLeft = false;
	}
	else if (collider->RightBottom().x > Define::StageWidth) {
		*collider = Point2D(Define::StageWidth - ColliderSize.x, collider->LeftTop().y);
		velocity->x = 0;
		isOnWall = true;
		if (!isOnLand)
			isFacingLeft = true;
	}
}

void Player::DrawImage(const int handle) const
{
	DrawRotaGraph(centerX - cameraX, centerY - cameraY, 1.0, 0.0, handle, true);
}

void Player::DrawImage(const int handle, const Vec2& offset) const
{
	DrawRotaGraph(centerX + offset.x - cameraX, centerY + offset.y - cameraY, 1.0, 0.0, handle, true);
}

void Player::DrawImageRotate(const int handle, const Vec2& angle) const
{
	DrawRotaGraph(centerX - cameraX, centerY - cameraY, 1.0, angle.RadAngle(), handle, true);
}

void Player::ChangeState(const EState newState)
{
	(this->*StateInit.at(newState))();
	state = newState;
}

void Player::NeutralInit()
{
	SetAnimTimer(RunAnimRoop, true);
}

void Player::NeutralUpdate()
{
	if (GetPushDown(EAction::Swing)) {
		if (!isOnLand && (GetPushStay(EAction::Left) || GetPushStay(EAction::Right)))
			ChangeState(EState::SmashReady);
		else
			ChangeState(EState::SwingReady);
		return;
	}
	if (GetPushDown(EAction::Down) && isOnLand) {
		ChangeState(EState::Crouch);
		return;
	}

	velocity->y += (GetPushStay(EAction::Jump) ? WeakGravity : Gravity) * Time::DeltaTime();

	if (GetPushStay(EAction::Jump)) {
		if (isOnLand) {
			velocity->y = JumpVelocity;
			isHorionalJump = velocity->x;
			animationTimer->Stop();
			isOnLand = false;
		}
		else if (GetPushDown(EAction::Jump) && canAirJump) {
			velocity->y = AirJumpVelocity;
			canAirJump = false;
			if (GetPushStay(EAction::Left))
				isFacingLeft = true;
			else if (GetPushStay(EAction::Right))
				isFacingLeft = false;
			SetAnimTimer(0.6);
		}
	}
	HorizontalMovement(true);
	if (((bool)GetPushStay(EAction::Left) ^ (bool)GetPushStay(EAction::Right))) {
		if (isOnLand && (!animationTimer->IsActive() || animationTimer->Max() != RunAnimRoop)) {
			animationTimer->Stop();
			animationTimer->SetMaxTime(RunAnimRoop);
			animationTimer->Start(true);
		}
	}
	else if (animationTimer->IsActive() && animationTimer->Max() == RunAnimRoop) {
		animationTimer->Stop();
	}
	if (isOnWall && !isOnLand && velocity->y > 0.0 && 
		((collider->Center().x < Stage::StageSize.x / 2 && GetPushStay(EAction::Left)) ||
			(collider->Center().x > Stage::StageSize.x / 2 && GetPushStay(EAction::Right)))) {
		ChangeState(EState::RubWall);
	}
}

void Player::NeutralDraw() const
{
	if (isOnLand) {
		if (velocity->x == 0.0) {
			DrawImage(imageHandles->stand[isFacingLeft]);
			return;
		}
		DrawImage(imageHandles->run[isFacingLeft][(int)(ImageHandles::RunFlame * animationTimer->ProgressRate())], Vec2(0, 10));
		return;
	}
	if (animationTimer->IsActive()) {
		DrawImage(imageHandles->airJump[isFacingLeft][(int)(ImageHandles::AirJumpFlame * animationTimer->ProgressRate())]);
	}
	else if (velocity->y < -SlowAnimThreshold) {
		if (isHorionalJump)
			DrawImage(imageHandles->jumpHoriAcc[isFacingLeft][(int)(ImageHandles::JumpHoriAccFlame * ((velocity->y - JumpVelocity) / ((-JumpVelocity - SlowAnimThreshold) * 2)))]);
		else
			DrawImage(imageHandles->jumpConst[isFacingLeft]);
	}
	else if (velocity->y < SlowAnimThreshold) {
		if (isHorionalJump)
			DrawImage(imageHandles->jumpHoriSlow[isFacingLeft][(int)(ImageHandles::JumpHoriSlowFlame * (SlowAnimThreshold + velocity->y) / (2 * SlowAnimThreshold))]);
		else
			DrawImage(imageHandles->jumpSlow[isFacingLeft][(int)(ImageHandles::JumpSlowFlame * (SlowAnimThreshold + velocity->y) / (2 * SlowAnimThreshold))]);
	}
	else
		DrawImage(imageHandles->jumpDown[isFacingLeft]);
}

void Player::RubWallInit()
{
	isFacingLeft = !isFacingLeft;
	SetAnimTimer(0.25);
	canAirJump = true;
	velocity->y = SpeedOnWall;
}

void Player::RubWallUpdate()
{
	if (GetPushDown(EAction::Jump)) {
		velocity->SetLength(JumpVelocity);
		velocity->SetAngle(isFacingLeft ? -Define::Pi * 3.0 / 4.0 : (-Define::Pi / 4.0));
		isHorionalJump = true;
		ChangeState(EState::Neutral);
	}
	if ((isFacingLeft && !GetPushStay(EAction::Right)) || (!isFacingLeft && !GetPushStay(EAction::Left)) || isOnLand) {
		ChangeState(EState::Neutral);
	}
	if (GetPushDown(EAction::Swing)) {
		ChangeState(EState::SwingReady);
	}
}

void Player::RubWallDraw() const
{
	if (animationTimer->IsActive())
		DrawImage(imageHandles->walling[isFacingLeft][(int)(ImageHandles::WallingFlame * animationTimer->ProgressRate())]);
	else
		DrawImage(imageHandles->wall[isFacingLeft]);
}

void Player::CrouchInit()
{
	collider->Top(Define::StageHeight - CrouchingColliderHeight, true);
}

void Player::CrouchUpdate()
{
	if (!GetPushStay(EAction::Down)) {
		ChangeState(EState::Neutral);
		collider->Top(Define::StageHeight - ColliderSize.y, true);
		return;
	}
	if (GetPushDown(EAction::Swing)) {
		ChangeState(EState::SwingReady);
		collider->Top(Define::StageHeight - ColliderSize.y, true);
		return;
	}
	velocity->x *= 0.9;
}

void Player::CrouchDraw() const
{
	DrawImage(imageHandles->crouch[isFacingLeft]);
}

void Player::SwingReadyInit()
{
	if (GetPushStay(EAction::Left))
		isFacingLeft = true;
	else if (GetPushStay(EAction::Right))
		isFacingLeft = false;
	SetAnimTimer(4.0 / 60.0);
	nonChargeSwingTimer->Start();
}

void Player::SwingReadyUpdate()
{
	velocity->y += Gravity * Time::DeltaTime();
	if (isOnLand) {
		velocity->x = 0.0;
	}
	else {
		HorizontalMovement(false);
	}
	if (nonChargeSwingTimer->IsFinishing()) {
		ChangeState(EState::SwingCharge);
		return;
	}
	if (!GetPushStay(EAction::Swing)) {
		ChangeState(EState::SwingAfter);
		return;
	}
	auto& ball = *GetScene()->FindGameObject<Ball>();
	if (swingCollider->IsCollided(ball.GetSweepCollider())) {
		if (ball.Swing(*this, 0.0)) {
			ChangeState(EState::HitStop);
			return;
		}
		return;
	}
}

void Player::SwingReadyDraw() const
{
	if (DebugMode::IsDebugMode())
		(*swingCollider - Vec2(cameraX, cameraY)).Draw(Color::Get(ColorID::Black));
	if (animationTimer->IsActive())
		DrawImage(imageHandles->swingReady[isFacingLeft][(int)(ImageHandles::SwingReadyFlame * animationTimer->ProgressRate())]);
	else
		DrawImage(imageHandles->swingCharge[isFacingLeft][1]);
}

void Player::SwingChargeInit()
{
	chargeTimer->Start();
}

void Player::SwingChargeUpdate()
{
	velocity->y += Gravity * Time::DeltaTime();
	if (isOnLand) {
		velocity->x = 0;
	}
	else {
		velocity->x *= 0.9;
	}
	if (GetPushDown(EAction::Bant) && special) {
		special = 0;
	}
	if (!GetPushStay(EAction::Swing) || chargeTimer->IsFinishing()) {
		auto& ball = *GetScene()->FindGameObject<Ball>();
		if (swingCollider->IsCollided(ball.GetSweepCollider())) {
			if (ball.Swing(*this, chargeTimer->IsFinishing() ? 0.0 : chargeTimer->ProgressRate())) {
				ChangeState(EState::HitStop);
				return;
			}
			return;
		}
		ChangeState(EState::SwingAfter);
		return;
	}
}

void Player::SwingChargeDraw() const
{
	if (DebugMode::IsDebugMode())
		(*swingCollider - Vec2(cameraX, cameraY)).Draw(Color::Get(ColorID::Black));
	DrawImage(imageHandles->swingCharge[isFacingLeft][(int)(chargeTimer->ProgressRate() * 4.0) % 2]);
}

void Player::SwingAfterInit()
{
	SetAnimTimer(17.0 / 60.0);
	swingAfterRigorTimer->Start();
}

void Player::SwingAfterUpdate()
{
	velocity->y += Gravity * Time::DeltaTime();
	if (isOnLand) {
		velocity->x = 0;
	}
	else {
		velocity->x *= 0.9;
	}
	if (!swingAfterRigorTimer->IsActive() && IsGettingAnyMoveInput()) {
		animationTimer->Stop();
		ChangeState(EState::Neutral);
		return;
	}
	if (animationTimer->IsFinishing()) {
		ChangeState(EState::Neutral);
		return;
	}
}

void Player::SwingAfterDraw() const
{
	DrawImage(imageHandles->swingAfter[isFacingLeft][(int)(ImageHandles::SwingAfterFlame * animationTimer->ProgressRate())]);
}

void Player::SmashReadyInit()
{
	if (GetPushStay(EAction::Left))
		isFacingLeft = true;
	else if (GetPushStay(EAction::Right))
		isFacingLeft = false;
	isSmashing = true;
	SetAnimTimer(SmashTime);
}

void Player::SmashReadyUpdate()
{
	velocity->y += Gravity * Time::DeltaTime();
	if (isOnLand) {
		velocity->x = 0.0;
	}
	else {
		HorizontalMovement(false);
	}
	if (animationTimer->IsFinishing()) {
		ChangeState(EState::Smash);
		return;
	}
	auto& ball = *GetScene()->FindGameObject<Ball>();
	if (swingCollider->IsCollided(ball.GetSweepCollider())) {
		if (ball.Swing(*this, 1.0)) {
			ChangeState(EState::HitStop);
			return;
		}
	}
}

void Player::SmashReadyDraw() const
{
	DrawImage(imageHandles->smashReady[isFacingLeft][(int)(ImageHandles::SmashReadyFlame * animationTimer->ProgressRate())]);
}

void Player::SmashInit()
{
}

void Player::SmashUpdate()
{
	velocity->y += Gravity * Time::DeltaTime();
	if (isOnLand) {
		ChangeState(EState::Neutral);
	}
	else {
		HorizontalMovement(false);
	}
}

void Player::SmashDraw() const
{
	DrawImage(imageHandles->smash[isFacingLeft]);
}

void Player::HitStopInit()
{
	if (GetPushStay(EAction::Up))
		swingDirection = Define::EDirection::Up;
	else if (GetPushStay(EAction::Down))
		swingDirection = Define::EDirection::Down;
	else if (GetPushStay(EAction::Left))
		swingDirection = Define::EDirection::Left;
	else
		swingDirection = Define::EDirection::Right;
	*velocity *= 0.0;
}

void Player::HitStopUpdate()
{
	if (GetPushDown(EAction::Up))
		swingDirection = Define::EDirection::Up;
	else if (GetPushDown(EAction::Down))
		swingDirection = Define::EDirection::Down;
	else if (GetPushDown(EAction::Left))
		swingDirection = Define::EDirection::Left;
	else if (GetPushDown(EAction::Right))
		swingDirection = Define::EDirection::Right;
	if (GetScene()->FindGameObject<Ball>()->IsOnCompleteBeingSwinged()) {
		ChangeState(EState::SwingAfter);
		return;
	}
}

void Player::HitStopDraw() const
{
	DrawImage(isSmashing ? imageHandles->smash[isFacingLeft] : imageHandles->swingAfter[isFacingLeft][0]);
}

void Player::DamagedInit()
{
	velocity->x = -2000;
	velocity->y = GetScene()->FindGameObject<Ball>()->GetVelocity().x >= 0.0 ? 100.0 : -100.0;
	collider->Bottom(collider->Top() + ColliderSize.x, true);
	collider->Right(collider->Left() + ColliderSize.y, true);
}

void Player::DamagedUpdate()
{
	if (isOnLand) {
		ChangeState(EState::Neutral);
	}
}

void Player::DamagedDraw() const
{
	DrawImageRotate(imageHandles->stand[isFacingLeft], Vec2(1, 0));
}

void Player::SetAnimTimer(const double newTime, const bool withoutStart)
{
	animationTimer->Stop();
	animationTimer->SetMaxTime(newTime);
	if(!withoutStart)
		animationTimer->Start();
}

void Player::HorizontalMovement(const bool canChangeFacing)
{
	if (((bool)GetPushStay(EAction::Left) ^ (bool)GetPushStay(EAction::Right))) {
		if (!wallJumpTimer->IsActive()) {
			if (GetPushStay(EAction::Left)) {
				if (isOnLand) {
					velocity->x = -SpeedHorizontal;
					if(canChangeFacing)
						isFacingLeft = true;
				}
				else {
					velocity->x += -SpeedHorizontal * 0.1;
					if (velocity->x < -SpeedHorizontal)
						velocity->x = -SpeedHorizontal;
				}
			}
			else if (GetPushStay(EAction::Right)) {
				if (isOnLand) {
					if(canChangeFacing)
						isFacingLeft = false;
					velocity->x = SpeedHorizontal;
				}
				else {
					velocity->x += SpeedHorizontal * 0.1;
					if (velocity->x > SpeedHorizontal)
						velocity->x = SpeedHorizontal;
				}
			}
		}
	}
	else {
		if (isOnLand) {
			velocity->x = 0;
		}
		else {
			velocity->x *= 0.9;
		}
	}
}

double Player::GetBallPossessHeight()
{
	return BallPossessHeight;
}

int Player::GetPlayerNo() const
{
	return playerNo;
}

const AABB2D& Player::GetCollider() const
{
	return *collider;
}

int Player::GetLife() const
{
	return life;
}

void Player::OnParried()
{
	isParried = true;
}

Define::ETeam Player::GetTeam() const
{
	return team;
}

Define::EDirection Player::GetInputDirection() const
{
	if (GetPushStay(EAction::Up)) {
		return Define::EDirection::Up;
	}
	if (GetPushStay(EAction::Down)) {
		return Define::EDirection::Down;
	}
	if (isFacingLeft && GetPushStay(EAction::Left)) {
		return Define::EDirection::Left;
	}
	if (!isFacingLeft && GetPushStay(EAction::Right)) {
		return Define::EDirection::Right;
	}
	return Define::EDirection::None;
}

Double2 Player::GetBallDegree() const
{
	const Double2 HorizontalDir = Double2(isFacingLeft ? -1 : 1, 1);
	if (isSmashing)
		return AirDownSwingDegree * HorizontalDir;
	switch (swingDirection)
	{
	case Define::EDirection::Up:
		return UpSwingDegree * HorizontalDir;
		break;
	case Define::EDirection::Down:
		if (isOnLand)
			return GroundDownSwingDegree * HorizontalDir;
		return AirDownSwingDegree * HorizontalDir;
		break;
	case Define::EDirection::Left:
	case Define::EDirection::Right:
	default:
		return Vec2(1.0, 0.0) * HorizontalDir;
		break;
	}
}

void Player::OnCompleteBeginSwing()
{
	ChangeState(EState::SwingAfter);
}

bool Player::IsGettingAnyMoveInput() const
{
	return GetPushStay(EAction::Up) || GetPushStay(EAction::Down) || GetPushStay(EAction::Left) || GetPushStay(EAction::Right) || GetPushStay(EAction::Jump) || GetPushStay(EAction::Swing);
}

void Player::AddDamage(const int speed)
{
	isGettingDamage = true;
	life -= 0.178 * speed + 23.58;
}

void Player::EndDamageStop()
{
	ChangeState(EState::Damaged);
}

int Player::GetPlayerNum()
{
	return playerNum;
}

Player::ImageHandles::ImageHandles(const int playerNo)
{
	const std::string filePathStr("data/image/");
	std::string colorStr;
	switch (playerNo)
	{
	case 0:colorStr = "_red";   break;
	case 1:colorStr = "_blue";  break;
	case 2:colorStr = "_yellow";break;
	case 3:colorStr = "_green"; break;
	default:break;
	}
	const std::string sideStr[2] = { "_right", "_left" };
	const std::string extentionStr = ".png";
	for (int i = 0; i < 2; i++) {
		const std::string latterStr = sideStr[i] + colorStr + extentionStr;
		stand[i] = LoadGraph((filePathStr + "stand" + latterStr).c_str());
		LoadDivGraph((filePathStr + "run" + latterStr).c_str(), 15, 4, 4, 960 / 4, 672 / 4, run[i]);
		crouch[i] = LoadGraph((filePathStr + "crouch" + latterStr).c_str());
		jumpAcc[i] = LoadGraph((filePathStr + "jumpAcc" + latterStr).c_str());
		jumpConst[i] = LoadGraph((filePathStr + "jumpConst" + latterStr).c_str());
		LoadDivGraph((filePathStr + "jumpSlow" + latterStr).c_str(), 3, 3, 1, 438 / 3, 196, jumpSlow[i]);
		jumpDown[i] = LoadGraph((filePathStr + "jumpDown" + latterStr).c_str());
		LoadDivGraph((filePathStr + "jumpHoriAcc" + latterStr).c_str(), 4, 2, 2, 508 / 2, 542 / 2, jumpHoriAcc[i]);
		LoadDivGraph((filePathStr + "jumpHoriSlow" + latterStr).c_str(), 2, 2, 1, 322 / 2, 253 / 1, jumpHoriSlow[i]);
		LoadDivGraph((filePathStr + "airJump" + latterStr).c_str(), 17, 6, 3, 1374 / 6, 699 / 3, airJump[i]);
		LoadDivGraph((filePathStr + "land" + latterStr).c_str(), 3, 3, 1, 543 / 3, 193, land[i]);
		wall[i] = LoadGraph((filePathStr + "wall" + latterStr).c_str());
		LoadDivGraph((filePathStr + "walling" + latterStr).c_str(), 6, 3, 2, 795 / 3, 550 / 2, walling[i]);
		LoadDivGraph((filePathStr + "swingReady" + latterStr).c_str(), 3, 3, 1, 372 / 3, 221, swingReady[i]);
		LoadDivGraph((filePathStr + "swingReady" + latterStr).c_str(), 3, 3, 1, 372 / 3, 221, swingReady[i]);
		LoadDivGraph((filePathStr + "swingCharge" + latterStr).c_str(), 2, 2, 1, 332 / 2, 223, swingCharge[i]);
		LoadDivGraph((filePathStr + "swingAfter" + latterStr).c_str(), 6, 3, 2, 870 / 3, 412 / 2, swingAfter[i]);
		LoadDivGraph((filePathStr + "smashReady" + latterStr).c_str(), 7, 4, 2, 1192 / 4, 508 / 2, smashReady[i]);
		smash[i] = LoadGraph((filePathStr + "smash" + latterStr).c_str());
		LoadDivGraph((filePathStr + "bantBefor" + latterStr).c_str(), 5, 3, 2, 840 / 3, 512 / 2, bantBefor[i]);
		LoadDivGraph((filePathStr + "bantAfter" + latterStr).c_str(), 4, 2, 2, 618 / 2, 692 / 2, bantAfter[i]);
	}
}

Player::ImageHandles::~ImageHandles()
{
	for (int i1 = 0; i1 < 2; i1++) {
		DeleteGraph(stand[i1]);
		for (int i2 = 0; i2 < ImageHandles::RunFlame; i2++)
			DeleteGraph(run[i1][i2]);
		DeleteGraph(crouch[i1]);
		DeleteGraph(jumpAcc[i1]);
		DeleteGraph(jumpConst[i1]);
		for (int i2 = 0; i2 < ImageHandles::JumpSlowFlame; i2++)
			DeleteGraph(jumpSlow[i1][i2]);
		DeleteGraph(jumpDown[i1]);
		for (int i2 = 0; i2 < ImageHandles::JumpHoriAccFlame; i2++)
			DeleteGraph(jumpHoriAcc[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::JumpHoriSlowFlame; i2++)
			DeleteGraph(jumpHoriSlow[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::AirJumpFlame; i2++)
			DeleteGraph(airJump[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::LandFlame; i2++)
			DeleteGraph(land[i1][i2]);
		DeleteGraph(wall[i1]);
		for (int i2 = 0; i2 < ImageHandles::WallingFlame; i2++)
			DeleteGraph(walling[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::SwingReadyFlame; i2++)
			DeleteGraph(swingReady[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::SwingChargeFlame; i2++)
			DeleteGraph(swingCharge[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::SwingAfterFlame; i2++)
			DeleteGraph(swingAfter[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::BantBeforFlame; i2++)
			DeleteGraph(bantBefor[i1][i2]);
		for (int i2 = 0; i2 < ImageHandles::BantAfterFlame; i2++)
			DeleteGraph(bantAfter[i1][i2]);
	}
}
