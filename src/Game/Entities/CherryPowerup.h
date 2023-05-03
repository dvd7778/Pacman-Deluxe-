#pragma once

#include "Powerup.h"
#include "Player.h"

class CherryPowerup : public Powerup{
    public:
        CherryPowerup(Player*, EntityManager*);
        void activate();
        int getRank();
    private:
        Player* pacman;
        EntityManager* entitymanager;
        int rank = 3;
};