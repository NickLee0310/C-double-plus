#ifndef _EXECUTION_H
#define _EXECUTION_H

#include <memory>
#include <queue>

#include "event.h"

class Execution
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
public:
	virtual void ExecuteOrder(const std::unique_ptr<Event>& InputSignal,
								QueueEvents& events) {};
};

class SimulatedExecution :public Execution
{
	using QueueEvents = std::queue<std::unique_ptr<Event> >;
public:
	void ExecuteOrder(const std::unique_ptr<Event>& InputSignal,
					QueueEvents& events);
};

#endif // !_EXECUTION_H
