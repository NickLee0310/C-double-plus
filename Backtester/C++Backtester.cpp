#include <iostream>
#include "backtest.h"
#include "strategy.h"


//#define block

class BuyAndHold :public Strategy
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using CurrentPositions = std::map<std::string, double>;
public:
	BuyAndHold(const std::vector<std::string>& inputStockList)
		:ifExecute(false), stockList(inputStockList)
	{
		for (auto stockName : stockList)
		{
			stockQuantity.insert({stockName, 0});
		}
	}
	void CalculateSignals(QueueEvents& events,
		const LatestBars& bars,
		const CurrentPositions& currentPositions)
	{
		if (!ifExecute)
		{
			//std::cout << "Calcualte signals" << std::endl;
			for (auto stockName : stockList)
			{
				stockQuantity[stockName] = 1000;
			}
			events.push(std::make_unique<SignalEvent>(stockQuantity));
			ifExecute = true;
		}
	}
private:
	bool ifExecute;
	std::vector<std::string> stockList;
	std::map<std::string, int> stockQuantity;
};


class MAcross :public Strategy
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using CurrentPositions = std::map<std::string, double>;

public:
	MAcross(const std::vector<std::string>& stockList)
		:stockList(stockList)
	{
		for (auto stockName : stockList)
		{
			stockQuantity.insert({ stockName, 0 });
			longMovingSum.insert({ stockName, 0.0 });
			shortMovingSum.insert({ stockName, 0.0 });
		}
	}
	void CalculateSignals(QueueEvents& events,
		const LatestBars& bars,
		const CurrentPositions& currentPositions)
	{
		static int count = 1;
		static int longWindow = 50;
		static int shortWindow = 20;
		static double longMA = 0.0;
		static double shortMA = 0.0;
		bool ifHaveSignal = false;

		for (auto stock : stockList)
		{
			longMovingSum[stock] += bars.at(stock).back().adjClose;
			shortMovingSum[stock] += bars.at(stock).back().adjClose;
			if (count > shortWindow)
			{
				shortMovingSum[stock] -= bars.at(stock)[bars.at(stock).size() - 1 - shortWindow].adjClose;
			} 
			if (count > longWindow)
			{
				longMovingSum[stock] -= bars.at(stock)[bars.at(stock).size() - 1 - longWindow].adjClose;
				longMA = longMovingSum[stock] / longWindow;
				shortMA = shortMovingSum[stock] / shortWindow;
				if (shortMA > longMA && currentPositions.at(stock) == 0)
				{
					stockQuantity[stock] = 1000;
					ifHaveSignal = true;

				}
				else if (shortMA < longMA && currentPositions.at(stock) > 0)
				{
					stockQuantity[stock] = -1000;
					ifHaveSignal = true;
				}
			}
		}
		if (ifHaveSignal)
		{
			auto itr = bars.cbegin();
			auto date = itr->second.back().date;
			std::cout << date << '\n';
			std::cout << "shortMA: " << shortMA << "  " << "longMA: " << longMA << '\n';
			events.push(std::make_unique<SignalEvent>(stockQuantity));
		}
		count++;
	}
private:
	std::vector<std::string> stockList;
	std::map<std::string, int> stockQuantity;
	std::map<std::string, double> longMovingSum;
	std::map<std::string, double> shortMovingSum;
};


int main()
{
#ifndef block

	std::string startDate{ "2010-01-03" };
	std::string endDate{ "2019-12-07" };
	std::vector<std::string> stockList{ "AAPL" };
	double initialCap{ 100000.0 };


	std::unique_ptr<Strategy> pStrat(std::make_unique<MAcross>(stockList));
	Backtest testEngine(stockList,
						startDate,
						endDate,
						initialCap,
						std::move(pStrat));
	testEngine.RunBacktesting();
	DisplayPortfolio(testEngine.GetTotalHoldings(), stockList);
	
#endif // !3
	return 0;
}