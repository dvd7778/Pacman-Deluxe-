#include "ChoosePlayerState.h"

ChoosePlayerState::ChoosePlayerState() {
    PacMan = new Button(ofGetWidth()/2-32, ofGetHeight()/3, 64, 50, "PacMan");
    MsPac = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Ms PacMan");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void ChoosePlayerState::tick() {
	anim->tick();
    PacMan->tick();
	if(PacMan->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
    MsPac->tick();
    if(MsPac->wasPressed()){
        choose = true;
        setNextState("Game");
		setFinished(true);
        
    }
}
void ChoosePlayerState::setChoose(bool c){
	choose = c;
}
bool ChoosePlayerState::getChoose(){
	return choose;
}
void ChoosePlayerState::render() {
	string title = "Choose your character";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	PacMan->render();
    MsPac->render();


}

void ChoosePlayerState::keyPressed(int key){
	
}

void ChoosePlayerState::mousePressed(int x, int y, int button){
	PacMan->mousePressed(x, y);
    MsPac->mousePressed(x,y);
}

Button* ChoosePlayerState::getMsPac(){
    return MsPac;
}

void ChoosePlayerState::reset(){
	setFinished(false);
	setNextState("");
	PacMan->reset();
    MsPac->reset();
}

ChoosePlayerState::~ChoosePlayerState(){
	delete PacMan;
    delete MsPac;
	delete anim;
}