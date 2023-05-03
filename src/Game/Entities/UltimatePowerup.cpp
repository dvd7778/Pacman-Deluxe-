#include "UltimatePowerup.h"

UltimatePowerup::UltimatePowerup(Player* p){
    this->pacman = p;
}

void UltimatePowerup::activate(){
    pacman->setCollection(pacman->sortCollection(pacman->getCollection(), 0));
}

int UltimatePowerup::getRank() { 
    return rank; 
}