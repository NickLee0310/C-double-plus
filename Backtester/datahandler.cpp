#ifndef  _DATA_HANDLER_CPP
#define _DATA_HANDLER_CPP

#include <iostream>
#include "event.h"
#include "datahandler.h"


using LatestBars = std::map<std::string, std::vector<BarData>>;
using LatestBar = std::map<std::string, BarData>;

//================HistoricCSVdataHandler====================


HistoricCSVdataHandler::HistoricCSVdataHandler(const std::vector<std::string>& inputStockList,
						const std::string& inputStartDate,
					      const std::string& inputEndDate) :
	bars(), latestBars(), latestBar(), continueBacktest(true), stockList(inputStockList),
	startDate(inputStartDate), endDate(inputEndDate)
{
	
	std::cout << "construct HistoricCSVdataHandler" << '\n';
	bars = CSVreader(stockList, startDate, endDate);
	for (auto itr = bars.cbegin(); itr != bars.cend(); ++itr)
	{
		latestBar.insert({ itr->first, BarData()});
		latestBars.insert({ itr->first, {} });
		latestBars[itr->first].reserve(bars[itr->first].size());
	}
}


//Gets the latestbar
const LatestBar& HistoricCSVdataHandler::GetLatestBar() 
{
	for (auto itr = latestBars.cbegin();
		itr != latestBars.cend();
		++itr)
	{
		latestBar[itr->first] = (itr->second).back();
	}
	return latestBar;
}


// updates bar and generates "Market" event
void HistoricCSVdataHandler::UpdateBars(QueueEvents& events)
									{
	//std::cout << "update bars!" << std::endl;
	for (auto stock : stockList)
	{
		try
		{
			latestBars[stock].push_back(bars[stock].front());
			bars[stock].pop_front();
			if (bars[stock].empty())
			{
				continueBacktest = false;
			}
		}
		catch (std::exception& exp)
		{
			std::cout << "UpdateBars fail before data.cend() in datahandler" << '\n';
			continueBacktest = false;
		}
	}
	events.push(std::make_unique<MarketEvent>());
	// update events
}


HistoricCSVdataHandler::~HistoricCSVdataHandler()
{
	std::cout << "destroy HistoricCSVdataHandler" << '\n';
}


std::unique_ptr<DataHandler> CreateDataHandler(const std::vector<std::string>& inputStockList,
					        const std::string& inputStartDate,
					        const std::string& inputEndDate)
{
	std::unique_ptr<DataHandler> ptr{ new HistoricCSVdataHandler(inputStockList,
								 inputStartDate,
								 inputEndDate) };
	return ptr;
}

#endif // ! _DATA_HANDLER_CPP



