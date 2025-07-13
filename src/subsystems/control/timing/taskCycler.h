#ifndef TASK_CYCLER_H
#define TASK_CYCLER_H
#include <vector>
typedef void * (Task)();

class TaskCycler
{
    public:
        TaskCycler();
        TaskCycler(std::vector<Task*> tasks);

        void update();
        void addTask(Task * task); // Add a new task to the end of the list
        void addTask(Task * task, int index); // Add a task to any index in the list (choose order)
        void dropTask(int taskIndex);
        Task * setTask(Task * newTask, int index); // returns the old task
        void swap(int index1, int index2); // Swaps the order of tasks.

    private:
        std::vector<Task*> tasks;
        
};
#endif