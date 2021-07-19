#pragma once
#include <list>
#include <vector>
#include <memory>

#include "Config.h"
#include "Primitive2D.h"
#include "Utility.h"

#include <assert.h>
#include <DxLib.h>
template <typename T>
class Cell;
template <typename T>
class Liner4TreeMgr;
class CollideCircle;

template<typename T>
class Collider {
public:
	Collider(T& object, Primitive2D& _shape, Liner4TreeMgr<T>* _pTree);
	~Collider();

	bool Update();
	T& object;
	Primitive2D& shape;
	Cell<T>* pCell;

private:
	unsigned long BitSeparate32(unsigned long n)
	{
		n = (n | (n << 8)) & 0x00ff00ff;
		n = (n | (n << 4)) & 0x0f0f0f0f;
		n = (n | (n << 2)) & 0x33333333;
		return (n | (n << 1)) & 0x55555555;
	}

	unsigned long Get2DMortonNumber(unsigned x, unsigned y)
	{
		return (BitSeparate32(x) | (BitSeparate32(y) << 1));
	}
};

template <typename T>
class Cell {
public:
	Cell(const int _idx, Liner4TreeMgr<T>* _pTree);
	~Cell();
	void Update();
	std::list<Collider<T>*> colliderList;
	const int idx;
	Liner4TreeMgr<T>* pTree;
};

template<typename T>
class CollidePair {
public:
	CollidePair(const Collider<T>* const _c1, const Collider<T>* const _c2) : c1(_c1), c2(_c2) {}

	const Collider<T>* const c1;
	const Collider<T>* const c2;
};

template<typename T>
class Liner4TreeMgr {
public:
	Liner4TreeMgr(const int _DevideLevel, const AABB2D& _flame);
	~Liner4TreeMgr();

	void Update();
	void Draw() const;

	void CreateCollider(T& parent, Primitive2D& shape);

private:
	void PushCollideStack(const int cellIdx);

public:
	static const int MaxLevelNum;
	int DevideLevel;
	int cellNum;
	int colliderNum;
	int OneSideCellNum;
	double CellWidth;
	double CellHeight;
	std::vector<int> cellNumInLevel;
	std::vector<int> cellNumStack;
	AABB2D flame;
	std::vector<Cell<T>*> cellVector;
	std::list<Collider<T>*> colliderStack;
	std::list<CollidePair<T>> collideList;
};

template <typename T>
const int Liner4TreeMgr<T>::MaxLevelNum = 9;

template <typename T>
Liner4TreeMgr<T>::Liner4TreeMgr(const int _DevideLevel, const AABB2D& _flame) :
	DevideLevel(_DevideLevel), colliderNum(0), flame(_flame)
{
	assert(_DevideLevel >= 0 && _DevideLevel <= MaxLevelNum);
	cellNum = 0;
	cellNumStack.push_back(0);
	OneSideCellNum = 1;
	for (int i = 0; i <= DevideLevel; i++) {
		cellNumInLevel.push_back(1);
		for (int i2 = 0; i2 < i; i2++) {
			cellNumInLevel.back() *= 4;
		}
		cellNum += cellNumInLevel.back();
		cellNumStack.push_back(cellNum);
		OneSideCellNum *= 2;
	}
	OneSideCellNum /= 2;
	CellWidth = flame.Width() / OneSideCellNum;
	CellHeight = flame.Height() / OneSideCellNum;
	for (int i = 0; i < cellNum; i++) {
		cellVector.push_back(new Cell<T>(i, this));
	}
}

template<typename T>
Liner4TreeMgr<T>::~Liner4TreeMgr()
{
	for (auto& it : cellVector) {
		if (it) {
			delete it;
			it = nullptr;
		}
	}
}

template <typename T>
void Liner4TreeMgr<T>::Update()
{
	for (auto& cell : cellVector)
		cell->Update();
	collideList.clear();
	PushCollideStack(0);
}

template <typename T>
void Liner4TreeMgr<T>::Draw() const
{
	const int FlameTop = flame.Top();
	const int FlameBottom = flame.Bottom();
	const int FlameLeft = flame.Left();
	const int FlameRight = flame.Right();
	printfDx("Collider Num : %d\n", colliderNum);
	const int roundRobin = (colliderNum * (colliderNum - 1) / 2);
	printfDx("Round Robin Collide : %d\n", roundRobin);
	printfDx("4 Tree Collide : %d\n", collideList.size());
	printfDx("Optimized Rate : %4.1lf%%\n", (double)(collideList.size()) / roundRobin * 100);
	/*for (int i = 0; i < OneSideCellNum + 1; i++) {
		int size = 1;
		int t = 2;
		for (int i2 = 0; i2 < DevideLevel - 1; i2++) {
			if (i % t)
				break;
			t *= 2;
			size += 1;
		}
		DrawLine(FlameLeft + CellWidth * i, FlameTop, FlameLeft + CellWidth * i, FlameBottom, Color::Get(ColorID::Gray), size);
		DrawLine(FlameLeft, FlameTop + CellHeight * i, FlameRight, FlameTop + CellHeight * i, Color::Get(ColorID::Gray), size);
	}*/
}

template <typename T>
void Liner4TreeMgr<T>::CreateCollider(T& object, Primitive2D& shape)
{
	cellVector.at(0)->colliderList.push_back(new Collider<T>(object, shape, this));
	colliderNum += 1;
}

template <typename T>
void Liner4TreeMgr<T>::PushCollideStack(const int cellIdx)
{
	if (cellIdx >= cellNum)
		return;
	const auto& colList = cellVector.at(cellIdx)->colliderList;
	for (auto it = colList.begin(); it != colList.end(); it++) {
		auto it2 = it;
		if (++it2 == colList.end())
			break;
		for (; it2 != colList.end(); it2++) {
			collideList.emplace_back(*it, *it2);
		}
	}
	for (const auto& it : colList)
		for (const auto& it2 : colliderStack)
			collideList.emplace_back(it, it2);

	int colliderCount = 0;
	for (const auto& it : colList) {
		colliderStack.push_back(it);
		colliderCount += 1;
	}
	for (int i = 0; i < 4; i++) {
		PushCollideStack(cellIdx * 4 + 1 + i);
	}
	for (int i = 0; i < colliderCount; i++)
		colliderStack.pop_back();
}

template <typename T>
Collider<T>::Collider(T& _object, Primitive2D& _shape, Liner4TreeMgr<T>* _pTree) :
	object(_object), shape(_shape), pCell(_pTree->cellVector.at(0))
{
}

template <typename T>
Collider<T>::~Collider()
{
}

template <typename T>
bool Collider<T>::Update()
{
	const AABB2D aabb = shape.GetAABB2D();
	const int CellWidth = pCell->pTree->CellWidth;
	const int CellHeight = pCell->pTree->CellHeight;
	const int OneSideCellNum = pCell->pTree->OneSideCellNum;
	const double FlameTop = pCell->pTree->flame.Top();
	const double FlameLeft = pCell->pTree->flame.Left();
	const int LTCellIdxX = Utility::Clamp(static_cast<int>((aabb.LeftTop().x - FlameLeft) / CellWidth), 0, OneSideCellNum - 1);
	const int LTCellIdxY = Utility::Clamp(static_cast<int>((aabb.LeftTop().y - FlameTop) / CellHeight), 0, OneSideCellNum - 1);
	const int RBCellIdxX = Utility::Clamp(static_cast<int>((aabb.RightBottom().x - FlameLeft) / CellWidth), 0, OneSideCellNum - 1);
	const int RBCellIdxY = Utility::Clamp(static_cast<int>((aabb.RightBottom().y - FlameTop) / CellHeight), 0, OneSideCellNum - 1);

	const unsigned long LTMorton = Get2DMortonNumber(LTCellIdxX, LTCellIdxY);
	const unsigned long RBMorton = Get2DMortonNumber(RBCellIdxX, RBCellIdxY);
	const unsigned long LevelCheckNo = LTMorton ^ RBMorton;

	int level = -1;
	int idxInLevel = 0;
	const int DevideLevel = pCell->pTree->DevideLevel;
	for (int i = 0; i < DevideLevel; i++) {
		if (LevelCheckNo >> ((DevideLevel - i - 1) * 2)) {
			level = i;
			idxInLevel = (RBMorton >> ((DevideLevel - i) * 2));
			break;
		}
		if (i == DevideLevel - 1)
			idxInLevel = RBMorton;
	}
	if (level == -1)
		level = DevideLevel;
	//DrawFormatString(shape.GetP().x + 2, shape.GetP().y + 2, Color::Get(ColorID::Gray), "L:%d, I:%d", level, idxInLevel);
	const int newCellIdx = pCell->pTree->cellNumStack.at(level) + idxInLevel;
	if (newCellIdx != pCell->idx) {
		pCell = pCell->pTree->cellVector.at(newCellIdx);
		pCell->colliderList.push_back(this);
		return true;
	}
	return false;
}

template <typename T>
Cell<T>::Cell(const int _idx, Liner4TreeMgr<T>* _pTree) :
	idx(_idx), pTree(_pTree)
{
}

template <typename T>
Cell<T>::~Cell()
{
	for (auto& collider : colliderList) {
		delete collider;
		collider = nullptr;
	}
	colliderList.clear();
}

template <typename T>
void Cell<T>::Update()
{
	for (auto it = colliderList.begin(); it != colliderList.end();) {
		if ((*it)->Update()) {
			it = colliderList.erase(it);
		}
		else
			it++;
	}
}
