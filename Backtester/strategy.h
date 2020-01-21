#ifndef  _STRATEGY_H
#define _STRATEGY_H

#include <memory>
#include <queue>
//#include <cstdarg>

#include "bar.h"
#include "event.h"

class Strategy
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using CurrentPositions = std::map<std::string, double>;
public:
	virtual void CalculateSignals(QueueEvents& events,
								  const LatestBars& bars,
								  const CurrentPositions& currentPositions) = 0;
};

#endif