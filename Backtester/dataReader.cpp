#ifndef _DATA_READER_CPP
#define _DATA_READER_CPP

#include <deque>

#include "dataReader.h"


BarData GetBar(const std::string& str)
{
	using std::cout;
	using std::endl;
	std::istringstream ss(str);
	std::string temp;
	BarData barTemp;
	try
	{
		std::getline(ss, temp, ',');
		barTemp.date = temp;
		std::getline(ss, temp, ',');
		barTemp.open = std::stod(temp);
		std::getline(ss, temp, ',');
		barTemp.high = std::stod(temp);
		std::getline(ss, temp, ',');
		barTemp.close = std::stod(temp);
		std::getline(ss, temp, ',');
		barTemp.low = std::stod(temp);
		std::getline(ss, temp, ',');
		barTemp.adjClose = std::stod(temp);
		std::getline(ss, temp, ',');
		barTemp.volume = std::stoi(temp);
	}
	catch (std::exception& exp)
	{
		cout << "exception in GetBar(): ";
		cout << exp.what() << endl;
	}
	return barTemp;
}



Bars CSVreader(const std::vector<std::string>& stockList,
			   const std::string& startDate,
			   const std::string& endDate)
{
	using std::cout;
	using std::endl;
	Bars data;
	for (auto stockName : stockList)
	{
		std::fstream myFile;
		myFile.open(stockName + ".csv", std::ios_base::in);
		std::list<BarData> bar;
		if (myFile.is_open())
		{
			std::cout << "file open success" << std::endl;
			std::string barString;
			unsigned int counter = 0;
			bool start = false;
			while (myFile.good())
			{
				try
				{
					std::getline(myFile, barString);
					if (counter == 0)
					{
						++counter;
						continue;
					}

					// checks if the row is empty 
					if (barString[0] == NULL)
						break;
					auto oneBar = GetBar(barString);
					// checks startDate
					if (oneBar.date >= startDate)
					{
						start = true;
					}
					// checks endDate
					if (oneBar.date >= endDate)
						break;
					if (start)
					{
						bar.push_back(oneBar);
					}
				}
				catch (std::exception& exp)
				{
					cout << "exception in CSVreader(): ";
					cout << exp.what() << endl;
				}
		
			}
			myFile.close();
		}
		else
			cout << "open() failed" << endl;
		data[stockName] = bar;
	}
	
	return data;
}


void DisplayYahooBarsData(const std::list<BarData>& bars)
{
	using std::cout;
	using std::endl;
	for (auto bar : bars)
	{
		DisplayOneYahooBar(bar);
	}
}

void DisplayOneYahooBar(const BarData& bar)
{
	using std::cout;
	using std::endl;
	cout << bar.date << " ";
	cout << bar.open << " ";
	cout << bar.high << " ";
	cout << bar.close << " ";
	cout << bar.low << " ";
	cout << bar.adjClose << " ";
	cout << bar.volume << " ";
	cout << endl;
}

#endif // !_DATA_READER_CPP
