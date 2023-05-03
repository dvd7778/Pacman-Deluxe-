#pragma once

#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        bool getDead();
        void setKillable(bool);
        void setDead(bool);
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        bool dead = false;
        void checkCollisions();
        int speed=2;
        EntityManager* em;
        Animation* killableAnim;
        Animation* ghostEyesAnim;
        vector<int> positionX;
        vector<int> positionY;

};