#pragma once

class Powerup{
    public:
        virtual void activate() = 0;
        virtual int getRank() = 0;
};