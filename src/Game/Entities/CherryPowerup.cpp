#include "CherryPowerup.h"

CherryPowerup::CherryPowerup(Player* p, EntityManager* em){
    this->pacman = p;
    this->entitymanager = em;
}

void CherryPowerup::activate(){
    int coords = ofRandom(0, entitymanager->entities.size());
    pacman->setBounds(entitymanager->entities[coords]->getX(), entitymanager->entities[coords]->getY());
}

int CherryPowerup::getRank(){ 
    return rank; 
}