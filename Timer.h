#pragma once

#include <list>

class Timer {

	friend void TimersUpdate();

public:
	//0 <= time < max
	Timer(const double _maxTimeSec);
	Timer(const Timer& obj);
	~Timer();

	Timer& operator =(const Timer& obj);

	void Start(const bool roop = false, const bool resetTime = true);
	void Stop();
	void Pause();

	double Time(const bool invert = false) const;
	double Max() const;
	bool IsActive() const;
	bool IsPausing() const;
	bool IsRooping() const;
	bool IsFinishing() const;

	//0.0 <= ProgressRate < 1.0
	double ProgressRate(const bool invert = false) const;

	void SetTime(const double _timeSec);

	//0以下の値に設定しようとするとmaxTimeが0.0にクランプされます
	//time以下の値に設定するとtimeが0.0にクランプされIsFinishing()の戻り値がtrueになります
	bool SetMaxTime(const double _maxTimeSec);

	void Print() const;

private:
	double time;
	double maxTime;
	bool isActive;
	bool isPausing;
	bool isRooping;
	bool isFinishing;
	std::list<Timer*>::iterator it;

	void Update();

};