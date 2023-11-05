#include "TimeLine.hpp"

std::chrono::milliseconds TimeLine::getRealTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}
