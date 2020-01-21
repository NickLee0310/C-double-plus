#ifndef _BAR_H
#define _BAR_H

struct BarData
{
	std::string date{ " " };
	double open{ 0.0 };
	double high{ 0.0 };
	double close{ 0.0 };
	double low{ 0.0 };
	double adjClose{ 0.0 };
	int volume{ 0 };
};



#endif // !_BAR_H

