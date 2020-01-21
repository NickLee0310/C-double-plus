#ifndef _BACKTEST_H
#define _BACKTEST_H

#include <memory>
#include <vector>
#include <map>

class Strategy;

class Backtest
{
	using TotalHoldings = std::map<std::string, std::map<std::string, double>>;
public:
	Backtest(const std::vector<std::string>& inputStockList,
		const std::string& inputStartDate,
		const std::string& inputEndDate,
		const double& inputInitCap,
		std::unique_ptr<Strategy>&& inputStrategy);
	void RunBacktesting();
	const TotalHoldings& GetTotalHoldings() const;
	~Backtest();
private:
	class BacktestImpl;
	std::unique_ptr<BacktestImpl> pImpl;
};

void DisplayPortfolio(const std::map<std::string, std::map<std::string, double>>& container,
	const std::vector<std::string>& stockLsit);

#endif // !_BACKTEST_H
