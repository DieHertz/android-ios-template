#include "Timer.h"

Timer::Timer() : mElapsed(0) {

}

void Timer::reset() {
    mElapsed = 0;
    mLastTime = now();
}

void Timer::update() {
    auto currentTime = now();
    mElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - mLastTime).count() * 1.0e-9;
    mLastTime = currentTime;
}

double Timer::elapsed() {
    return mElapsed;
}

std::chrono::steady_clock::time_point Timer::now() {
    return std::chrono::steady_clock::now();
}
