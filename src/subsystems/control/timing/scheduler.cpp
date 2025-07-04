#include "scheduler.h"

// Task constructor
Task::Task(TaskFunc * taskFunc, int interval, bool active)
    : taskFunc(taskFunc), interval(interval), active(active) {}

// Getter functions for Tasks
int Task::getInterval() {return interval;}
bool Task::isActive() {return isActive;}

// Mutators for Tasks
void Task::setInterval(int newInterval) {interval = newInterval;}
void Task::setActive(bool newState) {active = newState;}


// Scheduler constructor
Scheduler::Scheduler(std::vector<Task*> tasks, TimeTracker * timeTracker)
    : tasks(tasks), timeTracker(timeTracker)
    {
        recalculateTaskInfo(); // Constructs scheduleIntervals and activeTasks
    }


// addTask, dropTask, setTask, and swapTask all can invalidate task info, so recalculateTaskInfo needs to be called before any data is used.
// Add a task to end of the vector
void Scheduler::addTask(Task * task)
{
    tasks.push_back(task);
}

// Insert a task into some index
void Scheduler::addTask(Task * task, int index)
{
    tasks.insert(tasks.begin() + index, task);
}

// Remove any task 
void Scheduler::dropTask(int index)
{
    tasks.erase(tasks.begin() + index);
}

// Change one task to another, returns the old task
Task* Scheduler::setTask(Task * newTask, int index)
{
    Task* oldTask = tasks[index];
    tasks[index] = newTask;

    return oldTask;
}

// Swap the priorities of any two tasks
void Scheduler::swap(int index1, int index2)
{
    Task* tmp = tasks[index1];
    tasks[index1] = tasks[index2];
    tasks[index2] = tmp;
}

// Checks if the Scheduler's task info is up to date
bool Scheduler::validateTaskInfo()
{
    if(scheduleIntervals.size() != tasks.size())
        return false;

    for(int i = 0; i < tasks.size(); i++)
    {
        if(scheduleIntervals[i] != tasks[i]->getInterval())
            return false;
    }
    return true;
}

// Constructs scheduleIntervals and activeTasks
void Scheduler::recalculateTaskInfo()
{
    tasks.clear();
    for(int i = 0; i < tasks.size(); i++)
    {
        scheduleIntervals.push_back(tasks[i]->getInterval());
        activeTasks.push_back(tasks[i]->isActive());
    }
}