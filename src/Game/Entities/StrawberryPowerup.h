#pragma once

#include "Powerup.h"
#include "Player.h"

class StrawberryPowerup : public Powerup{
    public:
        StrawberryPowerup(Player*);
        void activate();
        int getRank();
    private:
        Player* pacman;
        int rank = 4;
};