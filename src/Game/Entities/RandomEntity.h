#pragma once

#include "Entity.h"

class RandomEntity: public Entity{
    public:
        RandomEntity(int, int, int, int, ofImage);
    private:
        int RandomSprite;
};