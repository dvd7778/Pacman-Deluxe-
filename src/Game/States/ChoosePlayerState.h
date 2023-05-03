#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 

class ChoosePlayerState : public State {
private:
	ofImage img1;
	Button *startButton;
    Button *PacMan;
    Button *MsPac;
	Animation* anim;
	bool choose = false;

public:
	ChoosePlayerState();
	~ChoosePlayerState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
    Button* getMsPac();
	void setChoose(bool);
	bool getChoose();
};