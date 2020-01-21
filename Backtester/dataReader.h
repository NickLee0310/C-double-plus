#ifndef _DATA_READER_H
#define _DATA_READER_H

#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <map>
#include <list>

#include "bar.h"

using Bars = std::map<std::string, std::list<BarData>>;

BarData GetBar(const std::string& str);

Bars CSVreader(const std::vector<std::string>& stockList,
	const std::string& startDate,
	const std::string& endDate);

void DisplayYahooBarsData(const std::list<BarData>& bars);

void DisplayOneYahooBar(const BarData& bar);

#endif // !_DATA_READER_H
