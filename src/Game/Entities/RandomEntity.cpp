#include "RandomEntity.h"

RandomEntity::RandomEntity(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height){
    RandomSprite = ofRandom(0, 4);
    if(RandomSprite == 0){
        sprite.cropFrom(spriteSheet,552,48,16,16); //melon
    } else if(RandomSprite == 1){
        sprite.cropFrom(spriteSheet,520,48,16,16); //citrus
    } else if(RandomSprite == 2){
        sprite.cropFrom(spriteSheet,536,48,16,16); //apple
    } else if(RandomSprite == 3){
        sprite.cropFrom(spriteSheet,568,48,16,16); //galaxian
    } else if(RandomSprite == 4){
        sprite.cropFrom(spriteSheet,600,48,16,16); //key
    }
}