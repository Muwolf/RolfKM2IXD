#include "Color.h"


Color::Color() {

}

void Color::newColor(float _numberColors, float _x, float _y, float _colorR, float _colorG, float _colorB) {
	x = _x;
	y = _y;
	colorR = _colorR;
	colorG = _colorG;
	colorB = _colorB;
	numberColors = _numberColors;

	color = ofColor(colorR, colorG, colorB, 255);

	width = ofGetWidth() / (numberColors * numberColors);
	height = ofGetHeight() / (numberColors);

	x = x*width;
	y = y*height;

	ofLog() << "Color: " << color << " X: " << x << " Y: " << y << endl;

}


void Color::update() {

}

void Color::draw() {
	ofSetColor(color);
	ofDrawRectangle(x, y, width, height);
}
