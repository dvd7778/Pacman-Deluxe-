#pragma once

#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "CherryEntity.h"
#include "StrawberryEntity.h"
#include "RandomEntity.h"
#include "UltimateEntity.h"

class MapBuilder {
    public:
        MapBuilder();
	Map* createMap(ofImage, string);
        void setLocationStrawberry1(int);
        void setLocationRandom1(int);
        void setLocationStrawberry2(int);
        void setLocationRandom2(int);

	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        int counter1 = 0;
        int locationCherry1 = ofRandom(0, 13);
        int locationCherry2 = ofRandom(14, 27);
        int locationStrawberry1 = ofRandom(0, 13);
        int locationStrawberry2 = ofRandom(14, 27);
        int locationRandom1 = ofRandom(0, 13);
        int locationRandom2 = ofRandom(14, 27);
        int xMatrix;
        int yMatrix;
        ofColor boundBoundBlock;
        ofColor pacman;
        ofColor ghostC;
	ofColor dotC;
	ofColor bigDotC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
};