#include "ProcessManagement.hpp"
#include <iostream>

ProcessManagement::ProcessManagement() {
    std::cout << "[ProcessManagement] Initialized\n";
}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    if (!task) {
        std::cerr << "[ProcessManagement] Cannot submit null task\n";
        return false;
    }

    taskQueue.push(std::move(task));
    std::cout << "[ProcessManagement] Task submitted\n";

    return true;
}

// Execute all tasks in the queue
void ProcessManagement::executeTasks() {
    std::cout << "[ProcessManagement] Starting task execution...\n";

    while (!taskQueue.empty()) {

        std::unique_ptr<Task> &task = taskQueue.front();

        std::cout << "Processing Task: " << task->toString() << "\n";

        taskQueue.pop();
    }

    std::cout << "[ProcessManagement] Task execution finished.\n";
}
