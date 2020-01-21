#ifndef _PORTFOLIO_CPP
#define _PORTFOLIO_CPP

#include <map>
#include <string>
#include <iostream>

#include "portfolio.h"

using QueueEvents = std::queue<std::unique_ptr<Event> >;
using CurrentPositions = std::map<std::string, double>;
using CurrentHoldings = std::map<std::string, double>;
using TotalHoldings = std::map<std::string, std::map<std::string, double>>;
using LatestBar = std::map<std::string, BarData>;

Portfolio::Portfolio(const std::vector<std::string>& inputStockList,
	const std::string& inputStartDate,
	const double& inputInitCap) :
	stockList(inputStockList), startDate(inputStartDate)
{
	std::cout << "construct Portfolio" << std::endl;
	for (auto stockName : stockList)
	{
		currentPositions[stockName] = 0.0;
		currentHoldings[stockName + " nev"] = 0;
	}
	currentHoldings["Cash"] = inputInitCap;
	currentHoldings["Commission"] = 0.0;
	currentHoldings["Total"] = inputInitCap;
	totalHoldings.insert({startDate, currentHoldings});
}


void Portfolio::UpdateHoldingsFromBar(const LatestBar& bar, const std::string& priceType)
{
	
	double total = 0.0;
	auto itr = bar.cbegin();
	auto curDate = (itr->second).date;
	while (itr != bar.cend())
	{
		if (priceType == "open")
		{
			currentHoldings[itr->first + " nev"] =
				(itr->second).open * currentPositions[itr->first];
		}
		else if (priceType == "adj_close")
		{
			currentHoldings[itr->first + " nev"] =
				(itr->second).adjClose * currentPositions[itr->first];
		}
		total += currentHoldings[itr->first + " nev"];
		++itr;
	}
	total += currentHoldings["Cash"];
	total -= currentHoldings["Commission"];
	currentHoldings["Total"] = total;
	totalHoldings.insert({curDate, currentHoldings});
	
}

void Portfolio::GenerateOrder(const std::unique_ptr<Event>& InputSignal,
	QueueEvents& events)
{
	auto stockQuantityFromSignal = InputSignal->GetStockQuantity();
	events.push(std::make_unique<OrderEvent>(stockQuantityFromSignal));
}

void Portfolio::UpdateHoldingsFromFill(LatestBar bar,
	const std::unique_ptr<Event>& InputFill)
{
	auto stockQuantityFromFill = InputFill->GetStockQuantity();
	double total = 0.0;
	auto itr = stockQuantityFromFill.cbegin();
	auto curDate = (bar.cbegin()->second).date;
	while (itr != stockQuantityFromFill.cend())
	{
		currentPositions[itr->first] += stockQuantityFromFill[itr->first];
		currentHoldings[itr->first + " nev"] +=
			bar[(itr->first)].open * (itr->second);
		currentHoldings["Cash"] -=
			bar[(itr->first)].open * (itr->second);
		total += currentHoldings[itr->first + " nev"];
		++itr;
	}
	total += currentHoldings["Cash"];
	total -= currentHoldings["Commission"];
	currentHoldings["Total"] = total;
	totalHoldings[curDate] = currentHoldings;
}

Portfolio::~Portfolio()
{
	std::cout << "destroy Portfolio" << std::endl;
}

std::unique_ptr<Portfolio> CreatePortfolio(const std::vector<std::string>& inputStockList,
					   const std::string& inputStartDate,
					   const double& inputInitCap)
{
	std::unique_ptr<Portfolio> ptr{ new Portfolio(inputStockList,
					              inputStartDate,
					              inputInitCap) };
	return ptr;
}


#endif // !_PORTFOLIO_CPP

