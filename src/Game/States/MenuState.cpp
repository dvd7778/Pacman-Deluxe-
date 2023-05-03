#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Start");
	playerButton = new Button(ofGetWidth()/2-32, ofGetHeight()/3, 64, 50, "Choose Player");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void MenuState::tick() {
	anim->tick();
	startButton->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
	playerButton->tick();
	if(playerButton->wasPressed()){
		setNextState("Choose");
		setFinished(true);
	}
}
void MenuState::render() {
	string title = "Pacman Project";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	startButton->render();
	playerButton->render();


}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
	playerButton->mousePressed(x,y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
	playerButton->reset();
}

MenuState::~MenuState(){
	delete startButton;
	delete playerButton;
	delete anim;
}