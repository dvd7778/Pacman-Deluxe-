#include "SpeedPowerup.h"

SpeedPowerup::SpeedPowerup(Player* p){
    this->pacman = p;
}

void SpeedPowerup::activate(){
    if (pacman->getSpeed() == 4){
        pacman->setSpeed(8);
    } else { pacman->setSpeed(4); }
}

int SpeedPowerup::getRank() { 
    return rank; 
}