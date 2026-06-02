#pragma once
#include <iostream>
#include <chrono>
#include <string>

class Timer {
    private:
        std::string name;
        std::chrono::high_resolution_clock::time_point start;

    public:
        Timer(const std::string& n) 
            : name(n), start(std::chrono::high_resolution_clock::now()) {}
        ~Timer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::cout << "[" << name << "] " << diff << " us\n";
        }
    };