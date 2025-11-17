#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>               
#include "../file_handling/IO.hpp"

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::string filePath;
    Action action;
    std::fstream f_stream;       

    Task(const std::string &path, Action act) : filePath(path), action(act){
        // Open file for both reading + writing in binary mode
        f_stream.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
        if (!f_stream.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }
    }

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

            return Task(filePath, action);   // <-- Constructor opens file
        } else {
            throw std::runtime_error("Invalid task format");
        }
    }
};

#endif

