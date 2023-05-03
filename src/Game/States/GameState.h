#pragma once

#include "State.h"
#include "Player.h"
#include "MapBuilder.h"
#include "Button.h"

class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		int getFinalScore();
		void setChosenPlayer(string);
		string getChosenPlayer();
	private:
		ofSoundPlayer music;
		ofImage mapImage;
		ofImage pacmanSpriteSheet;
		Map* map;
		int finalScore = 0;
		int counter = 0;
		string chosenPlayer;
};