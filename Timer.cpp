#include "Timer.h"

void Timer::start() {begin = Clock::now();}

void Timer::stop() {end = Clock::now();}
    
void Timer::print() const {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << duration.count() << " ms" << std::endl;
}