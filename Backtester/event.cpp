#ifndef _EVENT_CPP
#define _EVENT_CPP

#include<string>
#include "event.h"


const std::map<std::string, int>& Event::GetStockQuantity() const
{
	return std::map<std::string, int>();
}

//================MarketEvent====================

MarketEvent::MarketEvent()
	:type(EventType::Market)
{};

EventType MarketEvent::GetType() const
{
	return type;
}

//================SignalEvent====================

SignalEvent::SignalEvent(const std::map<std::string, int>& inputStockQuantity)
	:type(EventType::Signal), stockQuantityFromSignal(inputStockQuantity)
{};

EventType SignalEvent::GetType() const
{
	return type;
}

const std::map<std::string, int>& SignalEvent::GetStockQuantity() const
{
	return stockQuantityFromSignal;
}

//================OrderEvent====================

OrderEvent::OrderEvent(const std::map<std::string, int>& inputStockQuantity)
	:type(EventType::Order), stockQuantityFromOrder(inputStockQuantity)
{};

EventType OrderEvent::GetType() const
{
	return type;
}

const std::map<std::string, int>& OrderEvent::GetStockQuantity() const
{
	return stockQuantityFromOrder;
}
//================FillEvent====================

FillEvent::FillEvent(const std::map<std::string, int>& inputStockQuantity)
	:type(EventType::Fill), stockQuantityFromFill(inputStockQuantity)
{};

EventType FillEvent::GetType() const
{
	return type;
}

const std::map<std::string, int>& FillEvent::GetStockQuantity() const
{
	return stockQuantityFromFill;
}
#endif // !_EVENT_CPP

