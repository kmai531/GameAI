#pragma once
#include <chrono>
class TimeLine {

    protected:
        std::chrono::milliseconds startTime;
        float tic;
        bool isPaused;
        float last_paused_time;
        float ellapsed_paused_time;
    public:
        virtual std::chrono::milliseconds getRealTime();
        virtual bool getPaused() = 0;
        virtual float getTime() = 0;
        virtual void pause () = 0;
        virtual void changeTic(float ticSize) = 0;
};