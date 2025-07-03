#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "timeTracker.h"

typedef void * (TaskFunc)();

// This is only a very simple scheduler and only supports no parameter, void return types
// This will be greatly expanded upon by Polaris II, which will use the ALBATROSS RTOS

class Task
{
    public:
        Task(TaskFunc * taskFunc, int interval, bool active);
    private:
        TaskFunc * taskFunc;
        int interval;
        bool active;
};

class Scheduler
{
    public:
        Scheduler(Task ** tasks, TimeTracker * timeTracker);
        void update();
        void addTask(Task * task);
        void dropTask(int taskIndex);
        Task * setTask(int taskIndex, Task * newTask); // returns the old task
        void swapTaskOrder(int index1, int index2); // Swaps the priorities of tasks.

    private:
        TimeTracker * timeTracker;
        Task ** tasks; // array of task pointers
        int * scheduleIntervals; // array of each interval
};


#endif