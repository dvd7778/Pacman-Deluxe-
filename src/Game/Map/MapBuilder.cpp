#include "MapBuilder.h"


MapBuilder::MapBuilder(){
	entityManager = new EntityManager();
	pixelMultiplier = 16;
	boundBoundBlock = ofColor(0,0,0);
	pacman = ofColor(255,255, 0);
	ghostC = ofColor(25, 255,0);
	dotC = ofColor(255, 10, 0);
	bigDotC = ofColor(167, 0, 150);
	pacmanSpriteSheet.load("images/Background.png");
	tempBound.cropFrom(pacmanSpriteSheet, 603,18,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 615,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 635,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,57,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,75,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,116,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,136,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,174,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,155,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,192,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 664,232,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 494,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,208,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,223,16,16);
	bound.push_back(tempBound);//single
}

Map* MapBuilder::createMap(ofImage mapImage, string image){
	int xOffset = (ofGetWidth() - mapImage.getWidth()*pixelMultiplier)/2;
	int yOffset = (ofGetHeight() - mapImage.getHeight()*pixelMultiplier)/2;

	ofPixels pixels = mapImage.getPixels();
	xMatrix = mapImage.getWidth();
	yMatrix = mapImage.getHeight();
	int mapMatrix[xMatrix][yMatrix];
	Map* mapInCreation =  new Map(entityManager);
    for (int i = 0; i < mapImage.getWidth(); i++) {
        for (int j = 0; j < mapImage.getHeight(); j++) {
            ofColor currentPixel = pixels.getColor(i, j);
            int xPos = i*pixelMultiplier + xOffset;
            int yPos = j*pixelMultiplier + yOffset;
            if(currentPixel == boundBoundBlock){
                BoundBlock* BoundBoundBlock = new BoundBlock(xPos,yPos,pixelMultiplier,pixelMultiplier,getSprite(mapImage,i,j));
                mapInCreation->addBoundBlock(BoundBoundBlock);
				mapMatrix[i][j] = 0;
            }else if(currentPixel == pacman){
                Player* PacMan = new Player(xPos,yPos,pixelMultiplier,pixelMultiplier, entityManager, image);
				mapInCreation->setPlayer(PacMan);
				mapMatrix[i][j] = 2;
            }else if(currentPixel == ghostC){
                GhostSpawner* ghostSpawn = new GhostSpawner(xPos,yPos,pixelMultiplier,pixelMultiplier,entityManager, pacmanSpriteSheet);
                mapInCreation->setGhostSpawner(ghostSpawn);
				mapMatrix[i][j] = 0;
            }else if(currentPixel == dotC){
				Dot* dot = new Dot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
				mapInCreation->addEntity(dot);
				mapMatrix[i][j] = 1;
            }else if(currentPixel == bigDotC){

				while (locationCherry1 == locationStrawberry1 || locationCherry1 == locationRandom1 || locationStrawberry1 == locationRandom1 || locationCherry2 == locationStrawberry2 || locationCherry2 == locationRandom2 || locationStrawberry2 == locationRandom2)
				{
					if(locationCherry1 == locationStrawberry1)
						setLocationStrawberry1(ofRandom(0, 13));
					if(locationCherry1 == locationRandom1 || locationStrawberry1 == locationRandom1)
						setLocationRandom1(ofRandom(0, 13));
					if(locationCherry2 == locationStrawberry2)
						setLocationStrawberry2(ofRandom(14, 27));
					if(locationCherry2 == locationRandom2 || locationStrawberry2 == locationRandom2)
						setLocationRandom2(ofRandom(14, 27));
				}

				if(counter1 == locationCherry1 || counter1 == locationCherry2){
					CherryEntity* cherry = new CherryEntity(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
					mapInCreation->addEntity(cherry);
					counter1++;
					mapMatrix[i][j] = 4;

				} else if(counter1 == locationStrawberry1 || counter1 == locationStrawberry2){
					StrawberryEntity* strawberry = new StrawberryEntity(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
					mapInCreation->addEntity(strawberry);
					counter1++;
					mapMatrix[i][j] = 5;
				
				} else if(counter1 == locationRandom1 || counter1 == locationRandom2){
					RandomEntity* random = new RandomEntity(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
					mapInCreation->addEntity(random);
					counter1++;
					mapMatrix[i][j] = 3;
				} else {
                	BigDot* bigDot = new BigDot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                	mapInCreation->addEntity(bigDot);
					counter1++;
					mapMatrix[i][j] = 1;
				}
            }
        }

    }
    return mapInCreation;

}

void MapBuilder::setLocationStrawberry1(int LS1){ locationStrawberry1 = LS1; }
void MapBuilder::setLocationRandom1(int LR1){ locationRandom1 = LR1; }
void MapBuilder::setLocationStrawberry2(int LS2){ locationStrawberry2 = LS2; }
void MapBuilder::setLocationRandom2(int LR2){ locationRandom2 = LR2; }

ofImage MapBuilder::getSprite(ofImage mapImage, int i, int j){
	ofColor currentPixel = boundBoundBlock;
	ofPixels pixels = mapImage.getPixels();
	ofColor leftPixel;
	ofColor rightPixel;
	ofColor upPixel;
	ofColor downPixel;
	if (i>0) {
		leftPixel = pixels.getColor(i - 1, j);
	}else{
		leftPixel = pacman;

	}
	if (i<mapImage.getWidth()-1) {
		rightPixel = pixels.getColor(i + 1, j);
	}else{
		rightPixel= pacman;

	}
	if (j>0) {
		upPixel = pixels.getColor(i, j - 1);
	}else{
		upPixel = pacman;

	}
	if (j<mapImage.getHeight()-1) {
		downPixel = pixels.getColor(i, j + 1);
	}else{
		downPixel = pacman;

	}

	if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[1];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[2];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[3];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[4];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[5];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[6];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[7];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[8];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[9];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[10];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[11];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[12];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[13];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[14];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[15];
	}else{

		return  bound[0];
	}
}