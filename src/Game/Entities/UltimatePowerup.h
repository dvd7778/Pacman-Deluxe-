#pragma once

#include "Powerup.h"
#include "Player.h"

class UltimatePowerup : public Powerup{
    public:
        UltimatePowerup(Player*);
        void activate();
        int getRank();
    private:
        Player* pacman;
        int rank = 5;
};