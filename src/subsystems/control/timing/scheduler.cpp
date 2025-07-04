#include "scheduler.h"

Task::Task(TaskFunc * taskFunc, int interval, bool active)
    : taskFunc(taskFunc), interval(interval), active(active) {}

int Task::getInterval() {return interval;}
bool Task::isActive() {return isActive;}

void Task::setInterval(int newInterval) {interval = newInterval;}
void Task::setActive(bool newState) {active = newState;}



Scheduler::Scheduler(std::vector<Task*> tasks, TimeTracker * timeTracker)
    : tasks(tasks), timeTracker(timeTracker)
    {
        for(int i = 0; i < tasks.size(); i++)
        {
            scheduleIntervals.push_back(tasks[i]->getInterval());
            activeTasks.push_back(tasks[i]->isActive());
        }
    }

void Scheduler::addTask(Task * task)
{
    tasks.push_back(task);
}

void Scheduler::addTask(Task * task, int index)
{
    tasks.insert(tasks.begin() + index, task);
}

void Scheduler::dropTask(int index)
{
    tasks.erase(tasks.begin() + index);
}

Task* Scheduler::setTask(Task * newTask, int index)
{
    Task* oldTask = tasks[index];
    tasks[index] = newTask;
    recalculateTaskInfo();
    return oldTask;
}