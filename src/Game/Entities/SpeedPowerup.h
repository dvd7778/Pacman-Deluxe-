#pragma once

#include "Powerup.h"
#include "Player.h"

class SpeedPowerup : public Powerup{
    public:
        SpeedPowerup(Player*);
        void activate();
        int getRank();
    private:
        Player* pacman;
        int rank = 1;
};