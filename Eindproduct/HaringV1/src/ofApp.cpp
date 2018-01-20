#include "ofApp.h"
#define WIDTH 360
#define HEIGHT 240

//---------------------
void ofApp::setup() {

	//Arduino setup
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM9");
	arduino.sendFirmwareVersionRequest();

	pinAddButton = 6;
	pinRedButton = 3;
	pinGreenButton = 4;
	pinBlueButton = 5;

	//Cam setup
	grabber.listDevices();
	grabber.setDeviceID(0);
	grabber.initGrabber(WIDTH, HEIGHT);
	grabber.setDesiredFrameRate(30);
	
	colorImg.allocate(WIDTH, HEIGHT);
	grayImage.allocate(WIDTH, HEIGHT);
	grayBg.allocate(WIDTH, HEIGHT);
	grayDiff.allocate(WIDTH, HEIGHT);

	//"Photo" setup
	bLearnBackground = true;
	thresholdValue = 100;
	drawDebug = true;
	red = 0;
	green = 0;
	blue = 0;
	colorMod = 10;

	//RGB Led
	pinRedLed = 11;
	pinGreenLed = 9;
	pinBlueLed = 10;

	arduino.sendPwm(pinRedLed, 255 - red);
	arduino.sendPwm(pinGreenLed, 255 - green);
	arduino.sendPwm(pinBlueLed, 255 - blue);
}

//---------------------
void ofApp::update() {
	arduino.update();
	grabber.update();

	if (grabber.isFrameNew()) {
		colorImg.setFromPixels(grabber.getPixels());
		grayImage = colorImg;

		if (bLearnBackground == true) {
			grayBg = grayImage; 
			bLearnBackground = false;
		}

		if (takePhoto == true) {
			grayDiff.absDiff(grayBg, grayImage);
			grayDiff.threshold(thresholdValue);

			//findContours (Source image, min pixels, max pixels, nBlobs, fillgaps)
			contourFinder.findContours(grayDiff, 500, 10000000, 1, true);
			takePhoto = false;
		}
	}
}

//---------------------
void ofApp::draw() {

	if (drawDebug) {
		ofBackground(255);
		ofSetHexColor(0xffffff);
		colorImg.draw(10, 10);    // The incoming color image
		grayImage.draw(WIDTH + 20, 10);  // A gray version of the incoming video
		grayBg.draw(10, HEIGHT + 20);     // The stored background image
		grayDiff.draw(WIDTH + 20, HEIGHT + 20);  // The thresholded difference image

		ofNoFill();
		ofDrawRectangle(WIDTH + 20, HEIGHT + 20, WIDTH, HEIGHT);

		// Draw each blob individually from the blobs vector
		int numBlobs = contourFinder.nBlobs;
		for (int i = 0; i < numBlobs; i++) {
			contourFinder.blobs[i].draw(WIDTH+20, HEIGHT+20);
		}
	}
	else {
		ofBackground(0);
		grayDiff.draw(0, 0);  // The thresholded difference image
		ofNoFill();
		ofDrawRectangle(0, 0, WIDTH, HEIGHT);
		grayDiff.draw(0, 0);
		
		ofFill();
		ofSetColor(red, green, blue);
			ofBeginShape();
			for (int i = 0; i < blob->nPts; i++) {
				ofVertex(0 + blob->pts[i].x, 0 + blob->pts[i].y);
			}
			ofEndShape(true);
		}

	}
}


//---------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		bLearnBackground = true;
	}

	if (key == 'v') {
		takePhoto = true;
	}

	if (key == 'g' && drawDebug) {
		drawDebug = false;
		ofLog() << "Debug view: " << drawDebug << endl;
	}
	else if (key == 'g' && !drawDebug) {
		drawDebug = true;
		ofLog() << "Debug view: " << drawDebug << endl;
	}
}

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
	arduino.sendDigitalPinMode(pinRedLed, ARD_PWM);
	arduino.sendDigitalPinMode(pinGreenLed, ARD_PWM);
	arduino.sendDigitalPinMode(pinBlueLed, ARD_PWM);

	//Setup listeners for the input on the arduinoboard
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

void ofApp::digitalPinChanged(const int& pin) {

	if (arduino.getDigital(pinAddButton) == 1) {
		takePhoto = true;
		//silhouette.newSilhouette(red, green, blue); 
		ofLog() << "Take Photo" << endl;
	}

	if (arduino.getDigital(pinRedButton) == 1) {
		bLearnBackground = true;
		red += colorMod;
		if (red > 255) red = 0;
		arduino.sendPwm(pinRedLed, 255 - red);
		ofLog() << "Red: " << red << endl;
	}


	if (arduino.getDigital(pinGreenButton) == 1) {
		green += colorMod;
		if (green > 255) green = 0;
		arduino.sendPwm(pinGreenLed, 255 - green);
		ofLog() << "Green: " << green << endl;
	}


	if (arduino.getDigital(pinBlueButton) == 1) {
		blue += colorMod;
		if (blue > 255) blue = 0;
		arduino.sendPwm(pinBlueLed, 255 - blue);
		ofLog() << "Blue: " << blue << endl;
	}
}
