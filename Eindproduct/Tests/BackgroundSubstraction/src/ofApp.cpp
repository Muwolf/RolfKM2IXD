#include "ofApp.h"

//---------------------
void ofApp::setup() {
	grabber.listDevices();
	grabber.setDeviceID(2);
	grabber.initGrabber(640, 480);
	grabber.setDesiredFrameRate(30);


	colorImg.allocate(640, 480);
	grayImage.allocate(640, 480);
	grayBg.allocate(640, 480);
	grayDiff.allocate(640, 480);

	bLearnBackground = true;
	thresholdValue = 50;
}

//---------------------
void ofApp::update() {

	// Ask the video player to update itself.
	grabber.update();

	if (grabber.isFrameNew()) { // If there is fresh data...

								  // Copy the data from the video player into an ofxCvColorImage
		colorImg.setFromPixels(grabber.getPixels());

		// Make a grayscale version of colorImg in grayImage
		grayImage = colorImg;

		// If it's time to learn the background;
		// copy the data from grayImage into grayBg
		if (bLearnBackground == true) {
			grayBg = grayImage; // Note: this is 'operator overloading'
			bLearnBackground = false; // Latch: only learn it once.
		}

		if (takePhoto == true) {
			// Take the absolute value of the difference 
			// between the background and incoming images.
			grayDiff.absDiff(grayBg, grayImage);

			// Perform an in-place thresholding of the difference image.
			grayDiff.threshold(thresholdValue);

			// Find contours whose areas are betweeen 20 and 25000 pixels.
			// "Find holes" is true, so we'll also get interior contours.
			contourFinder.findContours(grayDiff, 20, 25000, 10, false);

			//takePhoto = false; 
		}
	}
}

//---------------------
void ofApp::draw() {
	ofBackground(255);

	ofSetHexColor(0xffffff);
	colorImg.draw(20, 20);    // The incoming color image
	grayImage.draw(680, 20);  // A gray version of the incoming video
	grayBg.draw(20, 520);     // The stored background image
	grayDiff.draw(680, 520);  // The thresholded difference image

	ofNoFill();
	ofDrawRectangle(680, 520, 640, 480);

	// Draw each blob individually from the blobs vector
	int numBlobs = contourFinder.nBlobs;
	for (int i = 0; i < numBlobs; i++) {
		contourFinder.blobs[i].draw(680, 520);
	}
}

//---------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		bLearnBackground = true;
	}

	if (key == 'v' || 'V') {
		takePhoto = true;
	}
}