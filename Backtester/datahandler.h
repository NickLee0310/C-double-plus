#ifndef  _DATA_HANDLER_H
#define _DATA_HANDLER_H

#include <queue>

#include "dataReader.h"
#include "event.h"

class DataHandler
{
	using Bars = std::map<std::string, std::list<BarData>>;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using LatestBar = std::map<std::string, BarData>;
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
public:
	virtual void UpdateBars(QueueEvents& events) = 0;
	virtual const LatestBars& GetLatestBars() const = 0;
	virtual const LatestBar& GetLatestBar() = 0;
	virtual bool ContinueRun() const =  0;
	virtual ~DataHandler() {};
};


class HistoricCSVdataHandler :public DataHandler
{
	using Bars = std::map<std::string, std::list<BarData>>;
	using LatestBars = std::map<std::string, std::vector<BarData>>;
	using LatestBar = std::map<std::string, BarData>;
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
public:
	HistoricCSVdataHandler(const std::vector<std::string>& inputList,
						   const std::string& startDate,
						   const std::string& endDate);
	// handle dynamic increased bars
	const LatestBars& GetLatestBars() const override
	{return latestBars;};
	const LatestBar& GetLatestBar() override;
	bool ContinueRun() const 
	{ return continueBacktest; } ;

	void UpdateBars(QueueEvents& events) override;
	~HistoricCSVdataHandler();

private:
	Bars bars;
	LatestBars latestBars;
	LatestBar latestBar;
	bool continueBacktest;
	std::vector<std::string> stockList;
	std::string startDate;
	std::string endDate;
};

std::unique_ptr<DataHandler> CreateDataHandler(const std::vector<std::string>& inputStockList,
						const std::string& inputStartDate,
						 const std::string& inputEndDate);

#endif // ! _DATA_HANDLER_H

 

 
