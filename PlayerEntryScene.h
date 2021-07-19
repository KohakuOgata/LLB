#pragma once
#include "SceneBase.h"
#include "Define.h"
#include <vector>
#include <tuple>

class IOnSceneChangedListener;
class Parameter;

class PlayerEntryScene :
	public SceneBase
{
public:
	PlayerEntryScene(IOnSceneChangedListener* _impl, const Parameter& _parameter);
	~PlayerEntryScene();

	void Update() override;
	void Draw() override;
	void DebugDraw() override;

private:
	void EntryUpdate();
	void TryEntryPlayer(const Define::EController controller);
	void GoGameMainScene();
	void ExitUpdate();
	void TryExitPlayer(const Define::EController controller);
public:

private:
	class PlayerInfo {
	public:
		PlayerInfo(const Define::EController _controller, const Define::ETeam _team);
		~PlayerInfo();

		Define::EController controller;
		Define::ETeam team;
	};
	std::vector<PlayerInfo> playerInfo;
	double initialBallSpeed;

	const static double DefaultInitialBallSpeed;
};

