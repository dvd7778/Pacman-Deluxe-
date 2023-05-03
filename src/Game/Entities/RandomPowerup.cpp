#include "RandomPowerup.h"

RandomPowerup::RandomPowerup(Player* p){
    this->pacman = p;
}

void RandomPowerup::activate(){
    random = ofRandom(0, 9);

    if(random == 0 || random == 1 || random == 2){
        pacman->setScore(pacman->getScore() + 50);
    } else if(random == 3 || random == 4){
        pacman->setScore(pacman->getScore() + 100);
    } else if(random == 5 || random == 6){
        pacman->setScore(pacman->getScore() + 250);
    } else if(random == 7 || random == 8){
        pacman->setScore(pacman->getScore() + 500);
    } else if(random == 9){
        pacman->setScore(pacman->getScore() + 1000);
    }
}

int RandomPowerup::getRank() { 
    return rank; 
}