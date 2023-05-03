#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage, getChosenPlayer());
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	else if(map->getEmpty()==true){
		setFinished(true);
		setNextState("win");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	if(map->getPlayer()->getScore() >= 1000 && counter == 0){
		pacmanSpriteSheet.load("images/Background.png");
		UltimateEntity* ultimate = new UltimateEntity(map->getEntityManager()->entities[150]->getX(), map->getEntityManager()->entities[150]->getY(), 16, 16, pacmanSpriteSheet);
		map->addEntity(ultimate);
		counter++;
	}
}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	if(key == 'p'){
		setFinished(true);
		setNextState("pause");
		finalScore = map->getPlayer()->getScore();
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
		map = MapBuilder().createMap(mapImage, getChosenPlayer());
		counter = 0;
		setFinished(false);
		setNextState("");
}

int GameState::getFinalScore(){
	return finalScore;
}

void GameState::setChosenPlayer(string chosenP){
	chosenPlayer = chosenP;
}

string GameState::getChosenPlayer(){
	return chosenPlayer;
}

GameState::~GameState(){
	delete map;
}