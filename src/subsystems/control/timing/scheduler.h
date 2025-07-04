#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "timeTracker.h"
#include <vector>

typedef void * (TaskFunc)();

// This is only a very simple scheduler and only supports no parameter, void return types
// This will be greatly expanded upon by Polaris II, which will use the ALBATROSS RTOS

// Tasks are essentially functions made to fit the scheduler. They include the base taskFunc
// Tasks also include an interval and an activity state to determine when and if they should run
class Task
{
    public:
        Task(TaskFunc * taskFunc, int interval, bool active);
        int getInterval();
        bool isActive();

        void setInterval(int newInterval);
        void setActive(bool newState);
    private:
        TaskFunc * taskFunc;
        int interval;
        bool active;
};


class Scheduler
{
    public:
        Scheduler(std::vector<Task*> tasks, TimeTracker * timeTracker);
        void update();
        void addTask(Task * task); // Add a new task to the end of the list (lowest priority)
        void addTask(Task * task, int index); // Add a task to any index in the list (choose priority)
        void dropTask(int taskIndex);
        Task * setTask(int taskIndex, Task * newTask); // returns the old task
        void swapTaskOrder(int index1, int index2); // Swaps the priorities of tasks.

        // These are used internally to make sure that scheduleIntervals and activeTasks are up to date.
        bool validateTaskInfo(); 
        void recalculateTaskInfo();
    private:
        TimeTracker * timeTracker;
        std::vector<Task*> tasks; // array of task pointers
        std::vector<int> scheduleIntervals; // array of each interval
        std::vector<bool> activeTasks;
};


#endif