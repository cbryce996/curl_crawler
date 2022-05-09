#pragma once
// Describes the type of task that can be taken by the thread pool.
// Tasks must contain a run function which will be called by the thread.
//
// Add functions for killing a task

class task
{
public:
	// Use sub-class detructor
	virtual ~task()
	{
	}
	// Run must be defined by sub-classes
	virtual void run() = 0;
};
