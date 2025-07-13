#include "taskCycler.h"

TaskCycler::TaskCycler() {}
TaskCycler::TaskCycler(std::vector<Task*> tasks)
    : tasks(tasks) {}

void TaskCycler::addTask(Task * task)
{
    tasks.push_back(task);
}

// Insert a task into some index
void TaskCycler::addTask(Task * task, int index)
{
    tasks.insert(tasks.begin() + index, task);
}

// Remove any task 
void TaskCycler::dropTask(int index)
{
    tasks.erase(tasks.begin() + index);
}


// Change one task to another, returns the old task
Task* TaskCycler::setTask(Task * newTask, int index)
{
    Task* oldTask = tasks[index];
    tasks[index] = newTask;

    return oldTask;
}

// Swap the priorities of any two tasks
void TaskCycler::swap(int index1, int index2)
{
    Task* tmp = tasks[index1];
    tasks[index1] = tasks[index2];
    tasks[index2] = tmp;
}


void TaskCycler::update()
{
    numTasks = tasks.size();

    taskIndex = (taskIndex + 1) % numTasks;
    currentTask = tasks[taskIndex];
    
    if(currentTask)
        currentTask();
    
}