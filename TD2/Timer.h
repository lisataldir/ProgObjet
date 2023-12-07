#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

class Timer{
private:
    std::chrono::time_point<Clock> begin;
    std::chrono::time_point<Clock> end;
public:
    void start();
    void stop();
    void print() const;
};

#endif