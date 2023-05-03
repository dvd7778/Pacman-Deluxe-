#include "CherryEntity.h"

CherryEntity::CherryEntity(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 488,48,16,16);
}