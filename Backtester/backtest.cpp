#ifndef _BACKTEST_CPP
#define _BACKTEST_CPP

#include <iostream>
#include <ctime>

#include "backtest.h"
#include "backtestImpl.h"
#include "datahandler.h"
#include "portfolio.h"
#include "strategy.h"
#include "execution.h"

using TotalHoldings = std::map<std::string, std::map<std::string, double>>;

//================Backtest====================



Backtest::Backtest(const std::vector<std::string>& inputStockList,
				   const std::string& inputStartDate,
				   const std::string& inputEndDate,
				   const double& inputInitCap,
				   std::unique_ptr<Strategy>&& inputStrategy)
	:pImpl(std::make_unique<BacktestImpl>(inputStockList,
										  inputStartDate,
										  inputEndDate,
										  inputInitCap,
										  std::move(inputStrategy)))
{
	//std::cout << "build backtest" << std::endl;
};

void Backtest::RunBacktesting()
{
	return pImpl->RunBacktesting();
}

const TotalHoldings& Backtest::GetTotalHoldings() const
{
	return pImpl->GetTotalHoldings();
}


Backtest::~Backtest()
{
	//std::cout << "destroy backtester" << std::endl;
}

//================BacktestImpl====================

Backtest::BacktestImpl::BacktestImpl(const std::vector<std::string>& inputStockList,
	const std::string& inputStartDate,
	const std::string& inputEndDate,
	const double& inputInitCap,
	std::unique_ptr<Strategy>&& inputStrategy) :
	events(),
	pData(CreateDataHandler(inputStockList,
		inputStartDate,
		inputEndDate)),
	pPort(CreatePortfolio(inputStockList,
		inputStartDate,
		inputInitCap)),
	pStrat(std::move(inputStrategy)),
	pExe(std::make_unique<SimulatedExecution>())
{

	std::cout << "build backtestImpl" << '\n';
}

void Backtest::BacktestImpl::RunBacktesting()
{
	clock_t start, stop;
	start = clock();
	while (pData->ContinueRun())
	{
		// updates market evevnt
		pData->UpdateBars(events);
		bool toNextBar = false;
		// handles events
		while (!events.empty() && !toNextBar)
		{
			auto& NewEvent = events.front();
			EventType NewEventType = NewEvent->GetType();
			switch (NewEventType)
			{
			
			case EventType::Market:
				//std::cout << "market event occurs" << std::endl;
				// Update portfolio by close price
				pPort->UpdateHoldingsFromBar(pData->GetLatestBar(), "adj_close");
				pStrat->CalculateSignals(events, pData->GetLatestBars(), pPort->GetCurrentPositions());
				break;
			
			case EventType::Signal:
				//std::cout << "signal event occurs" << std::endl;
				// transform signal to order
				pPort->GenerateOrder(NewEvent, events);
				break;
	
			case EventType::Order:
				//std::cout << "order event occurs" << std::endl;
				// Transform order to fill
				pExe->ExecuteOrder(NewEvent, events);
				// move to next bar to avoid look-ahead bias
				toNextBar = true;
				break;
			case EventType::Fill:
				//std::cout << "fill event occurs" << std::endl;
				// Update portfolio by open price
				pPort->UpdateHoldingsFromBar(pData->GetLatestBar(), "open");
				// Update portfolio from fill
				pPort->UpdateHoldingsFromFill(pData->GetLatestBar(),
					NewEvent);
				//toNextBar = true;
				break;
			default:
				break;
			}
			
			events.pop();
		}
	}
	stop = clock();
	std::cout << "backtest over! "<< double(stop - start) / CLOCKS_PER_SEC << " second" << '\n';
}

const TotalHoldings& Backtest::BacktestImpl::GetTotalHoldings() const
{
	return pPort->GetTotalHoldings();
}


Backtest::BacktestImpl::~BacktestImpl() 
{
	//std::cout << "destroy backtesterImpl" << std::endl;
};


void DisplayPortfolio(const TotalHoldings& container,
	const std::vector<std::string>& stockLsit)
{
	int calcCol = 0;
	for (auto element = container.cbegin();
		element != container.cend();
		++element)
	{
		if (calcCol == 0)
		{
			std::cout << "              ";
			auto barDara = element->second;
			for (auto col = barDara.cbegin();
				col != barDara.cend();
				++col)
			{
				std::cout << col->first << "         ";
			}
			std::cout << std::endl;
			++calcCol;
		}
		std::cout << element->first << "    ";

		auto val = element->second;
		for (auto col = val.cbegin();
			col != val.cend();
			++col)
		{
			std::cout << col->second << "            ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

#endif // !_BACKTEST_CPP


