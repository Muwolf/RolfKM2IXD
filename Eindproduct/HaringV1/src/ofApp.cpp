#include "ofApp.h"
#define WIDTH 640
#define HEIGHT 480

//---------------------
void ofApp::setup() {

	//Arduino setup
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM8");
	arduino.sendFirmwareVersionRequest();

	pinWhiteButton = 6;
	pinRedButton = 3;
	pinGreenButton = 4;
	pinBlueButton = 5;

	//Cam setup
	grabber.listDevices();
	grabber.setDeviceID(0);
	grabber.initGrabber(640, 480);
	grabber.setDesiredFrameRate(30);

	colorImg.allocate(640, 480);
	grayImage.allocate(640, 480);
	grayBg.allocate(640, 480);
	grayDiff.allocate(640, 480);


	//"Photo" setup
	bLearnBackground = true;
	thresholdValue = 100;
	drawDebug = true;
	takePhoto = false;
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

	for (int i = 0; i < silhouetteList.size(); i++) {
		silhouetteList[i].update();
		if (silhouetteList[i].alpha <= 0) {
			silhouetteList.erase(silhouetteList.begin() + i);
		}
	}

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
			if (contourFinder.blobs.size() > 0) {
			auto blob = contourFinder.blobs[0];
			
				ofLog() << "Push" << endl;
				for (int i = 0; i < blob.nPts; i++) {
					ofPoint point(blob.pts[i].x, 0 + blob.pts[i].y);
					shape.push_back(point);

				}
				silhouette.newSilhouette(shape, red, green, blue);
				silhouetteList.push_back(silhouette);
				takePhoto = false;
			}
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
			contourFinder.blobs[i].draw(WIDTH + 20, HEIGHT + 20);
		}
	}
	else {
		ofBackground(0);
		for (int i = 0; i < silhouetteList.size(); i++) {
			silhouetteList[i].draw();
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
		ofLog() << "Take Photo: " << takePhoto << endl; 
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
	arduino.sendDigitalPinMode(pinWhiteButton, ARD_INPUT);
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

	if (arduino.getDigital(pinWhiteButton) == 1) {
		takePhoto = true;
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
