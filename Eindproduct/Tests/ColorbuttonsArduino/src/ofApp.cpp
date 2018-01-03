#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//Arduino Setup
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	arduino.connect("COM4");
	arduino.sendFirmwareVersionRequest();


	//Start value variables

	radius = 100;

	colorR = 0;
	colorG = 0;
	colorB = 0;
	colorMod = 10; 
	color = ofColor(colorR, colorG, colorB);

	//Variables for difrent pins on the arduino board. This way you don't have to hardcode the pinnumbers. 

	pinRedButton = 5;
	pinGreenButton = 4;
	pinBlueButton = 3;
	pinAddButton = 2;
}

//--------------------------------------------------------------
void ofApp::update() {

	arduino.update();

	//Update all balls in the vector
	for (int i = 0; i < ballList.size(); i++) {
		ballList[i].update();
		if (ballList[i].color.a <= 0) {
			ballList.erase(ballList.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//Draw all balls in the vector
	for (int i = 0; i < ballList.size(); i++) {
		ballList[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version) {

	//Look for arduino, and show firmware
	ofLog() << "Arduino firmware found " << arduino.getFirmwareName()
		<< arduino.getMajorFirmwareVersion()
		<< arduino.getMinorFirmwareVersion() << endl;

	//Setup pins
	arduino.sendDigitalPinMode(pinAddButton, ARD_INPUT);
	arduino.sendDigitalPinMode(pinRedButton, ARD_INPUT);
	arduino.sendDigitalPinMode(pinGreenButton, ARD_INPUT);
	arduino.sendDigitalPinMode(pinBlueButton, ARD_INPUT);


	//Setup listeners for the input on the arduinoboard

	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}


//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int& pin) {

	//if addbutton is pressed, add a ball to the vector
	if (arduino.getDigital(pinAddButton) == 1) {
		ball.newBall(radius, colorR, colorG, colorB);
		ballList.push_back(ball);
		
	}

	//if popbutton is pressed, remove the last ball from the vector
	if (arduino.getDigital(pinRedButton) == 1) {
		colorR += colorMod;
		if (colorR >= 255) colorR = 0; 
		ofLog() << "Red: " << colorR << endl; 
		color = ofColor(colorR, colorG, colorB);
	}

	if (arduino.getDigital(pinGreenButton) == 1) {
		colorG += colorMod;
		if (colorG >= 255) colorG = 0;
		ofLog() << "Green: " << colorG << endl;
		color = ofColor(colorR, colorG, colorB);
	}

	if (arduino.getDigital(pinBlueButton) == 1) {
		colorB += colorMod;
		if (colorB >= 255) colorB = 0;
		ofLog() << "Blue: " << colorB << endl;
		color = ofColor(colorR, colorG, colorB);
	}
}
