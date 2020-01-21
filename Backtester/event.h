#ifndef  _EVENT_H
#define _EVENT_H

#include <string>
#include <map>
/*
Abstract base class
*/
enum class EventType
{
	Market,
	Signal,
	Order,
	Fill,
};

class Event
{
public:
	virtual EventType GetType() const = 0;
	virtual const std::map<std::string, int>& GetStockQuantity() const;
	virtual ~Event() {};
};

/*
Handles the event of receiving a new market update
*/
class MarketEvent :public Event
{
public:
	MarketEvent();
	EventType GetType() const override;
private:
	EventType type;
};

/*
Handles the event of sending a signal from a Strategy object
*/
class SignalEvent :public Event
{
public:
	SignalEvent(const std::map<std::string, int>& inputStockQuantity);
	EventType GetType() const override;
	const std::map<std::string, int>& GetStockQuantity() const;
private:
	EventType type;
	std::map<std::string, int> stockQuantityFromSignal;
};

/*
Handles the event of sending a Order to a execution system
*/
class OrderEvent :public Event
{
public:
	OrderEvent(const std::map<std::string, int>& inputStockQuantity);
	EventType GetType() const override;
	const std::map<std::string, int>& GetStockQuantity() const;
private:
	EventType type;
	std::map<std::string, int> stockQuantityFromOrder;
};

/*
Encapsulate th notion of a Filled Order
*/
class FillEvent :public Event
{
public:
	FillEvent(const std::map<std::string, int>& inputStockQuantity);
	EventType GetType() const override;
	const std::map<std::string, int>& GetStockQuantity() const;
private:
	EventType type;
	std::map<std::string, int> stockQuantityFromFill;
};
#endif // ! _EVENT_H

