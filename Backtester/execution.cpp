#ifndef _EXECUTION_CPP
#define _EXECUTION_CPP

#include <iostream>


#include "execution.h"

void SimulatedExecution::ExecuteOrder(const std::unique_ptr<Event>& InputSignal,
										QueueEvents& events)
{
	auto stockQuantityFromOrder = InputSignal->GetStockQuantity();
	events.push(std::make_unique<FillEvent>(stockQuantityFromOrder));
}



#endif // !_EXECUTION_CPP
