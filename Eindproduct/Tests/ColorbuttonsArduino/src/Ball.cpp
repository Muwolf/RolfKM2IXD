#include "Ball.h"

Ball::Ball() {
};


//Function for new ball
void Ball::newBall(float _radius, float _colorR, float _colorG, float _colorB) {
	
	colorR = _colorR; 
	colorG = _colorG;
	colorB = _colorB;
	alpha = 255;	
	
	radius = _radius;
	x = ofRandom(radius, ofGetWidth() - radius);
	y = ofRandom(radius, ofGetHeight() - radius);
	color.set(colorR, colorG, colorB, alpha);
	ofLog() << "NEW BALL" << endl;
}


void Ball::update() {
	alpha = alpha - 0.1;
	color.set(colorR, colorG, colorB, alpha);
}


void Ball::draw() {
	//draw ball in the set color.
	ofSetColor(color);
	ofDrawCircle(x, y, radius);
}

