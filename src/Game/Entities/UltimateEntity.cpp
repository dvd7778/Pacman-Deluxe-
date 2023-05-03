#include "UltimateEntity.h"

UltimateEntity::UltimateEntity(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,584,48,16,16); //bell
}