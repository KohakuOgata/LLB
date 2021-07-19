#pragma once
#include "GameObject.h"
#include "Define.h"
#include <memory>
#include <array>
#include <vector>
#include <functional>

class Point2D;
class Vec2;
class AABB2D;
class Button;
enum class InputID;
class Double2;
class Timer;

class Player :
	public GameObject
{
public:
	enum class EAction {
		Up,
		Down,
		Left,
		Right,
		Jump,
		Swing,
		Bant,
		Catch,
		EmoteMiddle,
		EmoteUp,
		EmoteDown,
		EmoteLeft,
		EmoteRight,
		Escape,

		Num
	};

	class EState {
	public:
		EState(const int _state) : state(_state) {}
		operator int() const { return state; }
		
		int state;

		enum {
			Neutral,
			Crouch,
			RubWall,
			SwingReady,
			SwingCharge,
			SwingAfter,
			HitStop,
			Damaged,
			Down,
			Killed
		};
	};
public:
	Player(SceneBase* _pScene);
	~Player();

	void Start() override;
	void Update() override;
	void Draw() override;
	void DebugDraw() override;

	void SetController(const Define::EController _controller);
	void SetTeam(const Define::ETeam _team);
	Point2D GetBallPossessPos() const;
	static double GetBallPossessHeight();
	int GetPlayerNo() const;
	const AABB2D& GetCollider() const;
	void OnParried();
	Define::ETeam GetTeam() const;
	Define::EDirection GetInputDirection() const;
	Double2 GetBallDegree() const;
	void OnCompleteBeginSwing();
	bool IsGettingAnyMoveInput() const;
	void AddDamage(const int speed);

private:
	double GetPushStay(const EAction action) const;
	bool GetPushDown(const EAction action) const;
	bool GetPushUp(const EAction action) const;
	void VelocityUpdate();
	void PositionUpdate();
	void WallCollideUpdate();
	void DrawImage(const int handle) const;
	void DrawImage(const int handle, const Vec2& offset) const;
	void ChangeState(const EState newState);
	void NeutralInit();
	void NeutralUpdate();
	void NeutralDraw() const;
	void RubWallInit();
	void RubWallUpdate();
	void RubWallDraw() const;
	void CrouchInit();
	void CrouchUpdate();
	void CrouchDraw() const;
	void SwingReadyInit();
	void SwingReadyUpdate();
	void SwingReadyDraw() const;
	void SwingChargeInit();
	void SwingChargeUpdate();
	void SwingChargeDraw() const;
	void SwingAfterInit();
	void SwingAfterUpdate();
	void SwingAfterDraw() const;
	void HitStopInit();
	void HitStopUpdate();
	void HitStopDraw() const;
	void SetAnimTimer(const double newTime, const bool withoutStart = false);
	void HorizontalMovement(const bool canChangeFacing);
	
	std::vector<void(Player::*)()> StateInit;
	std::vector<void(Player::*)()> StateUpdate;
	std::vector<void(Player::*)() const> StateDraw;

public:
	const static double BallPossessHeight;
	const static double BallPossessWidth;

private:
	static int playerNum;

	int playerNo;
	Define::EController controller;
	Define::ETeam team;
	int stock;
	int life;
	int special;
	bool isLive;
	bool isFacingLeft;
	EState state;
	std::unique_ptr<Vec2> velocity;
	std::unique_ptr<Vec2> acceleration;
	std::unique_ptr<AABB2D> collider;
	std::unique_ptr<AABB2D> swingCollider;
	bool isOnLand;
	bool isOnWall;
	bool isRubbingWall;
	bool canAirJump;
	bool isHorionalJump;
	bool isCrouching;
	std::unique_ptr<Timer> animationTimer;
	std::unique_ptr<Timer> wallJumpTimer;
	bool isParried;
	bool isSwinging;
	bool isSmashing;
	std::unique_ptr<Timer> nonChargeSwingTimer;
	std::unique_ptr<Timer> chargeTimer;
	Define::EDirection swingDirection;
	std::unique_ptr<Timer> swingAfterRigorTimer;

	class ImageHandles {
	public:
		ImageHandles(const int playerNo);
		~ImageHandles();

		const static int RunFlame = 15;
		const static int JumpSlowFlame = 3;
		const static int JumpHoriAccFlame = 4;
		const static int JumpHoriSlowFlame = 2;
		const static int AirJumpFlame = 17;
		const static int LandFlame = 3;
		const static int WallingFlame = 6;
		const static int SwingReadyFlame = 3;
		const static int SwingChargeFlame = 2;
		const static int SwingAfterFlame = 6;
		const static int BantBeforFlame = 5;
		const static int BantAfterFlame = 4;

		int stand       [2] = { -1 };
		int run         [2][RunFlame] = { -1 };
		int crouch      [2] = { -1 };
		int jumpAcc     [2] = { -1 };
		int jumpConst   [2] = { -1 };
		int jumpSlow    [2][JumpSlowFlame] = { -1 };
		int jumpDown    [2] = { -1 };
		int jumpHoriAcc [2][JumpHoriAccFlame] = { -1 };
		int jumpHoriSlow[2][JumpHoriSlowFlame] = { -1 };
		int airJump     [2][AirJumpFlame] = { -1 };
		int land        [2][LandFlame] = { -1 };
		int wall        [2] = { -1 };
		int walling     [2][WallingFlame] = { -1 };
		int swingReady  [2][SwingReadyFlame] = { -1 };
		int swingCharge [2][SwingChargeFlame] = { -1 };
		int swingAfter  [2][SwingAfterFlame] = { -1 };
		int bantBefor   [2][BantBeforFlame] = { -1 };
		int bantAfter   [2][BantAfterFlame] = { -1 };
	};

	std::unique_ptr<ImageHandles> imageHandles;

	const static Double2 ColliderSize;
	const static Double2 SwingColliderSize;
	const static double CrouchingColliderHeight;
	const static double SpeedHorizontal;
	const static double SpeedOnWall;
	const static double Gravity;
	const static double WeakGravity;
	const static double JumpVelocity;
	const static double AirJumpVelocity;
	const static double ImmidiatelySwingTime;
	const static double MaxChargeTime;
	const static Vec2 UpSwingDegree;
	const static Vec2 GroundDownSwingDegree;
	const static Vec2 AirDownSwingDegree;
	const static Vec2 ForwardSpikeDegree;
	const static Vec2 BackweardSpikeDegree;
	const static double SwingAfterRigor;
};

