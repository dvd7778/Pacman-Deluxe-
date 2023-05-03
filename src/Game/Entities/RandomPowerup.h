#pragma once

#include "Powerup.h"
#include "Player.h"

class RandomPowerup : public Powerup{
    public:
        RandomPowerup(Player*);
        void activate();
        int getRank();
    private:
        Player* pacman;
        int random;
        int rank = 2;
};