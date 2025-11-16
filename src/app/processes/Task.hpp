#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include <sstream>
#include "../file_handling/IO.hpp"

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::string filePath;
    Action action;

    Task(const std::string &path, Action act)
        : filePath(path), action(act) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    static Task fromString(const std::string &taskData) {
        std::istringstream iss(taskData);
        std::string filePath, actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action =
                (actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);

            return Task(filePath, action);   // No file opening here
        } else {
            throw std::runtime_error("Invalid task format");
        }
    }
};


#endif
