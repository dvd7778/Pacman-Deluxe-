#include "StrawberryPowerup.h"

StrawberryPowerup::StrawberryPowerup(Player* p){
    this->pacman = p;
}

void StrawberryPowerup::activate(){
    pacman->setTimer(0);
    pacman->setInvincible(true);
}

int StrawberryPowerup::getRank() { 
    return rank; 
}