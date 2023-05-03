#include "Ghost.h"
#include "BoundBlock.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Entity(x, y, width, height){
    this->em = em;
    vector<ofImage> killableFrames;
    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    killableFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    killableFrames.push_back(temp);
    killableAnim = new Animation(10, killableFrames);

    vector<ofImage> eyeFrames;
    ofImage temp2;
    temp2.cropFrom(spriteSheet,584,78,16,16);
    eyeFrames.push_back(temp2);
    ghostEyesAnim = new Animation(10, eyeFrames);

    if(color == "red")      sprite.cropFrom(spriteSheet,456,64,16,16);
    else if(color=="pink")  sprite.cropFrom(spriteSheet,456,78,16,16);
    else if(color=="cyan")  sprite.cropFrom(spriteSheet,456,96,16,16);
    else if(color=="orange")sprite.cropFrom(spriteSheet,456,113,16,16);
    

}

void Ghost::tick(){
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if(dead == false){
        if(canMove){
            positionX.push_back(x);
            positionY.push_back(y);
            if(facing == UP){
                y-= speed;
            }else if(facing == DOWN){
                y+=speed;
            }else if(facing == LEFT){
                x-=speed;
            }else if(facing == RIGHT){
                x+=speed;
            }
        }else{
            int randInt;
            if(justSpawned){
                randInt = ofRandom(2);

            }else{
                randInt = ofRandom(4);
            }
            if(randInt == 0){
                facing = LEFT;
            }else if(randInt == 1){
                facing = RIGHT;
            }else if(randInt == 2){
                facing = DOWN;
            }else if(randInt == 3){
                facing = UP;
            }
            justSpawned = false;

        }
    } else{
        if(positionX.size() < 1 && positionY.size() < 1){
            setDead(false);
            justSpawned = true;
            facing = UP;
        } else{
            x = positionX.back();
            y = positionY.back();
            positionX.pop_back();
            positionY.pop_back();
        }
    }
}

void Ghost::render(){
    if(dead){
        ghostEyesAnim->getCurrentFrame().draw(x,y,width,height);
    }else if(killable){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }else{
        Entity::render();
    }
}

bool Ghost::getKillable(){
    return killable;
}
void Ghost::setKillable(bool k){
    killable = k;
}
bool Ghost::getDead(){
    return dead;
}
void Ghost::setDead(bool d){
    dead = d;
}

void Ghost::checkCollisions(){
    for(BoundBlock* BoundBlock: em->boundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
}

Ghost::~Ghost(){
    delete killableAnim;
    delete ghostEyesAnim;
}