#include "StrawberryEntity.h"

StrawberryEntity::StrawberryEntity(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,504,48,16,16);
}