#pragma once
#include "GameObject.h"

#include "Define.h"

#include "Primitive2D.h"

#include <memory>

class Timer;
class Player;

class Ball :
	public GameObject
{
public:
	class EPlayer {
	public:
		EPlayer(const int player = None):value(player){}
		operator int() { return value; }
		int value;
		enum {
			None,
			P1,
			P2,
			P3,
			P4
		};
	};
	enum class EState {
		Initiation,
		Possessed,
		Static,
		Banted,
		BeingSwinged,
		Swinged
	};

public:
	Ball(SceneBase* _pScene);
	~Ball();

	void Start() override;
	void Update() override;
	void Draw() override;
	void DebugDraw() override;

	void SetInitialSpeed(const double _initialSpeed);
	void Bant(const Define::EDirection direction);
	bool Swing(Player& player, const double chargedRate);
	const Circle2D& GetCollider() const;
	Cupsule2D GetSweepCollider() const;
	bool IsOnCompleteBeingSwinged() const;
	int GetSpeed();

private:
	void ChangeState(const EState nextState);
	void InitiationUpdate();
	void StaticInit();
	void PossessdUpdate();
	void BantedUpdate();
	void SwingedInit(const Player& player, const double chargedTime);
	void BeingSwingedUpdate();
	void SwingedUpdate();
	void StartPossessd(Player* _possessdPlayer);
	bool WallCollide();
	double GetActualSpeed() const;

public:
	const static double Radius;

private:
	std::unique_ptr<Circle2D> collider;
	std::unique_ptr<Vec2> vel;
	int speed;
	double initialSpeed;
	Define::ETeam color;
	EState state;
	std::unique_ptr<Timer> respawnAnimTimer;
	std::unique_ptr<Timer> possessdTimer;
	Player* possessedPlayer;
	bool isPossessed;
	std::unique_ptr<Timer> hitstopTimer;
	int swingedSamePlayerNum;
	EPlayer lastSwingedPlayer;
	bool onCompleteBeingSwinged;

	const Point2D InitialPos;
	const static double RespawnAnimTime;
	const static double InitiationMoveSpeed;
	const static double PossessedTime;
	const static double Gravity;
	const static double ParriedInitialVel;
	const static double ActualSpeedFactor;
	const static double HitstopFactor;
};