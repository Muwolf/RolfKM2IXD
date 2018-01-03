#pragma once

#include "ofMain.h"
#include "Ball.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();


	//All the variables needed for the balls
	vector<Ball> ballList;
	Ball ball;
	float radius;
	ofColor color;

	float colorR;
	float colorG;
	float colorB;
	float colorMod;


	//Variables for the arduino pins. This way they're not hardcoded, and can be easly changed in the future. 
	int pinRedButton;
	int pinGreenButton; 
	int pinBlueButton; 
	int pinAddButton;


	//Arduino functions
private:
	ofArduino arduino;
	void setupArduino(const int& version);
	void digitalPinChanged(const int& pin);

};