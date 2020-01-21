#ifndef _BACKTEST_IMPL_H
#define _BACKTEST_IMPL_H

#include <memory>
#include <queue>
#include <vector>
#include <list>

#include "backtest.h"

class Event;
class Portfolio;
class DataHandler;
class Strategy;
class Execution;

class Backtest::BacktestImpl
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
public:
	BacktestImpl(const std::vector<std::string>& inputStockList,
				 const std::string& inputStartDate,
				 const std::string& inputEndDate,
				 const double& inputInitCap,
				 std::unique_ptr<Strategy>&& inputStrategy);
	void RunBacktesting();
	const TotalHoldings& GetTotalHoldings() const;
	~BacktestImpl();

private:
	QueueEvents events;
	std::unique_ptr<DataHandler> pData;
	std::unique_ptr <Portfolio> pPort;
	std::unique_ptr<Strategy> pStrat;
	std::unique_ptr<Execution> pExe;
};

#endif
