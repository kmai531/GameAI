#include "GameTimeLine.hpp"

GameTimeLine::GameTimeLine(float new_Tic) {
    changeTic(new_Tic);
    startTime = getRealTime();
    isPaused = false;
    last_paused_time = 0;
    ellapsed_paused_time = 0;
}

void GameTimeLine::changeTic(float new_Tic) {
    tic = new_Tic;
}

bool GameTimeLine::getPaused() {
    return isPaused;
}

float GameTimeLine::getTime() {
    if(isPaused) {
        return last_paused_time;
    } else {
        std::chrono::milliseconds elapsed = getRealTime() - startTime;
        return elapsed.count() / (tic * 1e3) - ellapsed_paused_time;
    }
}

void GameTimeLine::pause() {
    // pause the game
    if(!isPaused) {
        last_paused_time = getTime();
        isPaused = true;
    } else {
        std::chrono::milliseconds elapsed = getRealTime() - startTime;
        ellapsed_paused_time = (elapsed.count() / (tic * 1e3)) - last_paused_time;
        isPaused = false;
    }
}

