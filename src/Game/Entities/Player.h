#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "Powerup.h"

enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        int timer;
	    bool invincible = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        Powerup* speedUp;
        Powerup* cherry;
        Powerup* strawberry;
        Powerup* random;
        Powerup* ultimate;
        vector<Powerup*> collection;

    public:
        Player(int, int, int , int, EntityManager*, string);
        ~Player();
        int getHealth();
        int getScore();
        int getSpeed();
        int getTimer();
        FACING getFacing();
        vector<Powerup*> getCollection();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void setSpeed(int);
        void setBounds(int, int);
        void setCollection(vector<Powerup*>);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        void setTimer(int);
		void setInvincible(bool);
        Powerup* compare(Powerup*, Powerup*);
        vector<Powerup*> sortCollection(vector<Powerup*>, int);
};