#ifndef _PORTFOLIO_H
#define _PORTFOLIO_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <deque>
#include <queue>

#include "bar.h"
#include "event.h"
#include "strategy.h"


class Portfolio
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
	using CurrentPositions = std::map<std::string, double>;
	using CurrentHoldings = std::map<std::string, double>;
	using TotalHoldings = std::map<std::string, std::map<std::string, double>>;
	using LatestBar = std::map<std::string, BarData>;

public:
	Portfolio(const std::vector<std::string>& inputStockList,
			  const std::string& inputStartDate,
			  const double& inputInitCap);
	const TotalHoldings& GetTotalHoldings() const {return totalHoldings; };
	const CurrentPositions& GetCurrentPositions() const { return currentPositions;};
	void UpdateHoldingsFromBar(const LatestBar& bar, const std::string& PriceType);
	void GenerateOrder(const std::unique_ptr<Event>& InputSignal,
		QueueEvents& events);
	void UpdateHoldingsFromFill(LatestBar bar,
				    const std::unique_ptr<Event>& InputFill);
	~Portfolio();
private:
	CurrentPositions currentPositions;
	CurrentHoldings currentHoldings;
	TotalHoldings totalHoldings;
	std::vector<std::string> stockList;
	std::string startDate;
};


std::unique_ptr<Portfolio> CreatePortfolio(const std::vector<std::string>& inputStockList,
					   const std::string& inputStartDate,
					   const double& inputInitCap);

#endif // !_PORTFOLIO_H



