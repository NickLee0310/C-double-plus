#ifndef _NAME_H
#define _NAME_H

#include<queue>
#include<deque>
#include<map>
#include<string>

#include "dataReader.h"
#include "event.h"

namespace myName
{
	using Bars = std::map<std::string, std::deque<BarData>>;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using LatestBar = std::map<std::string, BarData>;
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
	using CurrentPositions = std::map<std::string, double>;
	using CurrentHoldings = std::map<std::string, double>;
	using TotalHoldings = std::map<std::string, std::map<std::string, double>>;
}



#endif // ! _NAME_H
