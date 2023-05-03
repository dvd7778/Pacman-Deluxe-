#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "SpeedPowerup.h"
#include "CherryPowerup.h"
#include "CherryEntity.h"
#include "StrawberryEntity.h"
#include "StrawberryPowerup.h"
#include "RandomEntity.h"
#include "RandomPowerup.h"
#include "UltimateEntity.h"
#include "UltimatePowerup.h"

Player::Player(int x, int y, int width, int height, EntityManager* em, string image) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load(image);

    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);

    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }

    if(image == "images/pacman.png"){
        left.cropFrom(sprite, 0, 16, 16, 16);
        right.cropFrom(sprite, 0, 0, 16, 16);
        
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 16, 16, 16);
            leftAnimframes.push_back(temp);
        }
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 0, 16, 16);
            rightAnimframes.push_back(temp);
        }
    } else {
        left.cropFrom(sprite, 0, 0, 16, 16);
        right.cropFrom(sprite, 0, 16, 16, 16);
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 0, 16, 16);
            leftAnimframes.push_back(temp);
        }
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 16, 16, 16);
            rightAnimframes.push_back(temp);
        }
    }

    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    moving = MLEFT;
}

void Player::tick(){
    if(invincible) { timer++; }
    if(timer >= 300) { invincible = false; }

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if(invincible==false){
        if(facing == UP)
            walkUp->getCurrentFrame().draw(x, y, width, height);
        else if(facing == DOWN)
            walkDown->getCurrentFrame().draw(x, y, width, height);
        else if(facing == LEFT)
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        else if(facing == RIGHT)
            walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);

    ofDrawBitmapString("Power-Up Collection:", ofGetWidth()/2+325, 250); //**Prints collected power ups on the screen
    for(int i = 0; i<collection.size(); i++){
        if(collection[i]->getRank() == 2){
            ofDrawBitmapString("- Random Power-Up", ofGetWidth()/2+325, i*20 + 285);
        }
        if(collection[i]->getRank() == 3){
            ofDrawBitmapString("- Cherry Power-Up", ofGetWidth()/2+325, i*20 + 285);
        }
        if(collection[i]->getRank() == 4){
            ofDrawBitmapString("- Strawberry Power-Up", ofGetWidth()/2+325, i*20 + 285);
        }
    }
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':
            if(health == 3){
                break;
            }
            else{
                health++;
            }
            break;
        case 'y':
            for(Entity* entity:em->entities){
                    if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity) || dynamic_cast<CherryEntity*>(entity) || dynamic_cast<StrawberryEntity*>(entity) || dynamic_cast<RandomEntity*>(entity) || dynamic_cast<UltimateEntity*>(entity)){
                        entity->remove = true;
                        score += 25;
                    }
            }
            break;
        case ' ':
            speedUp = new SpeedPowerup(this);
            dynamic_cast<SpeedPowerup *>(speedUp);
            speedUp->activate();
            break;
        case 'f':                                   //** Activates saved up power ups in the collection
            if(collection.size()>0){
                collection[0]->activate();
                collection.erase(collection.begin());
            }
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

Powerup* Player::compare(Powerup* powerup1, Powerup* powerup2){ //** Compares the ranks between power ups
    if(powerup1->getRank() >= powerup2->getRank()){
        return powerup1;
    }
    return powerup2;
}

vector<Powerup*> Player::sortCollection(vector<Powerup*> collection, int index){ //**Sorts power ups based on ranks from high to low
    for(int i=1; i<collection.size(); i++){
        int j = i;
        while((j>0) && (compare(collection[j], collection[j-1]) == collection[j])){
            Powerup* temp = collection[j];
            collection[j] = collection[j-1];
            collection[j-1] = temp;
            j--;
        }
    }
    return collection;
}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
int Player::getSpeed(){ return speed; }
int Player::getTimer(){ return timer; }
FACING Player::getFacing(){ return facing; }
vector<Powerup*> Player::getCollection(){ return collection; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
void Player::setSpeed(int s){ speed = s;}
void Player::setTimer(int t){ timer = t; }
void Player::setInvincible(bool inv){ invincible = inv; }
void Player::setCollection(vector<Powerup*> c){
    collection.erase(collection.begin(), collection.end());
    collection = c;
}

void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity) || dynamic_cast<CherryEntity*>(entity) || dynamic_cast<StrawberryEntity*>(entity) || dynamic_cast<RandomEntity*>(entity) || dynamic_cast<UltimateEntity*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            if(dynamic_cast<CherryEntity*>(entity)){
                cherry = new CherryPowerup(this, this->em);
                dynamic_cast<CherryPowerup *>(cherry);
                collection.push_back(cherry);
                break;
                }
            if(dynamic_cast<StrawberryEntity*>(entity)){
                strawberry = new StrawberryPowerup(this);
                dynamic_cast<StrawberryPowerup *>(strawberry);
                collection.push_back(strawberry);
                break;
                }
            if(dynamic_cast<RandomEntity*>(entity)){
                random = new RandomPowerup(this);
                dynamic_cast<RandomPowerup *>(random);
                collection.push_back(random);
                break;
                }
            if(dynamic_cast<UltimateEntity*>(entity)){
                ultimate = new UltimatePowerup(this);
                dynamic_cast<UltimatePowerup *>(ultimate);
                ultimate->activate();
                break;
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getDead() == false){
                if(ghost->getKillable()){
                    ghost->setDead(true);
                }
                else if(invincible == false)
                    die();
            }
        }
    }

    
}

void Player::setBounds(int X, int Y) {
    x = X;
    y = Y;
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}