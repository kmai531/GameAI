#pragma once
#include "TimeLine.hpp"

class GameTimeLine : public TimeLine {
    public:
        GameTimeLine(float ticSize);
        bool getPaused() override;
        float getTime() override;
        void pause() override;
        void changeTic(float ticSize) override;
};