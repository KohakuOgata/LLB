#include "timer.h"

#include "Config.h"
#include "Utility.h"
#include "Time.h"

#include <list>
#include <DxLib.h>

namespace {
	std::list<Timer*> timers = {};
}

void TimersUpdate() {
	for (auto& it : timers)
		it->Update();
}

Timer::Timer(const double _maxTime)
	:time(0), maxTime(_maxTime), isActive(false), isPausing(false), isRooping(false), isFinishing(false)
{
	timers.push_back(this);
	it = --timers.end();
}

Timer::Timer(const Timer& obj)
{
	time      = obj.time;
	maxTime   = obj.maxTime;
	isActive  = obj.isActive;
	isPausing = obj.isPausing;
	isRooping = obj.isRooping;
	timers.push_back(this);
	it = --timers.end();
}

Timer::~Timer()
{
	timers.erase(it);
}

Timer& Timer::operator=(const Timer& obj)
{
	time      = obj.time;
	maxTime   = obj.maxTime;
	isActive  = obj.isActive;
	isPausing = obj.isPausing;
	isRooping = obj.isRooping;
	return *this;
}

void Timer::Start(const bool roop, const bool resetTimer)
{
	isRooping = roop;
	if (resetTimer)
		time = 0;
	isActive = true;
}

void Timer::Stop()
{
	time = 0;
	isActive = false;
	isPausing = false;
	isRooping = false;
}

void Timer::Pause()
{
	isPausing = true;
}

double Timer::Time(const bool invert) const
{
	if (!invert)
		return time;
	return maxTime - time;
}

double Timer::Max() const
{
	return maxTime;
}

bool Timer::IsActive() const
{
	return isActive;
}

bool Timer::IsPausing() const
{
	return isPausing;
}

bool Timer::IsRooping() const
{
	return isRooping;
}

bool Timer::IsFinishing() const
{
	return isFinishing;
}

double Timer::ProgressRate(const bool invert) const
{
	if (!invert)
		return time / maxTime;
	return 1.0 - time / maxTime;
}

void Timer::SetTime(const double _time)
{
	time = max(0.0, _time);
	if (time < maxTime)
		return;
	time = 0.0;
	isFinishing = true;
}

bool Timer::SetMaxTime(const double _maxTime)
{
	maxTime = max(0.0, _maxTime);

	if (time < maxTime)
		return true;

	time = 0.0;
	isFinishing = true;
	return false;
}

void Timer::Print() const
{
	printfDx(
		"time[flame] : %-10d, maxTime[flame] : -10d\ntime[second] : %-12.2f, maxTime[second] : %-12.2f\nisActive : %-5s, isPausing : %-5s, isRooping : %-5s\n\n",
		time, maxTime, (double)time / Config::FPS, (double)maxTime / Config::FPS, 
		isActive ? "true" : "false", isPausing ? "true" : "false", isRooping ? "true" : "false");
}

void Timer::Update()
{
	isFinishing = false;
	if (!isActive || isPausing)
		return;
	time += Time::DeltaTime();
	if (time >= maxTime) {
		time = 0;
		isFinishing = true;
		if (!isRooping)
			isActive = false;
	}
}
