#ifndef Timer_h
#define Timer_h

#include <chrono>

class Timer {
public:
    Timer();

    void reset();
    void update();

    double elapsed();

private:
    std::chrono::steady_clock::time_point now();

    double mElapsed;
    std::chrono::steady_clock::time_point mLastTime;
};

#endif /* Timer_h */
