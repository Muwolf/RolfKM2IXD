#include "ofApp.h"

void ofApp::setup() {
	grabber.listDevices();
	grabber.setDeviceID(1);
	grabber.initGrabber(GRABBER_WIDTH, GRABBER_HEIGHT);
	grabber.setDesiredFrameRate(30);

	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	saturation.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	value.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT); 
	filtered2.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}

void ofApp::update() {
	grabber.update();
	if (grabber.isFrameNew()) {
		rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();

		hsvImage.convertToGrayscalePlanarImages(hue, saturation, value);

		for (int i = 0; i < GRABBER_WIDTH * GRABBER_HEIGHT; i++) {
			if (ofInRange(hue.getPixels()[i], selectedHue - HUE_MARGIN, selectedHue + HUE_MARGIN)) {
				filtered.getPixels()[i] = 255;
			}
			else {
				filtered.getPixels()[i] = 0;
			}
		}

		filtered.flagImageChanged();

		contours.findContours(filtered, 50, GRABBER_WIDTH * GRABBER_HEIGHT / 2, 1, false);

		for (int i = 0; i < GRABBER_WIDTH * GRABBER_HEIGHT; i++) {
			if (ofInRange(hue.getPixels()[i], selectedHue2 - HUE_MARGIN, selectedHue2 + HUE_MARGIN)) {
				filtered2.getPixels()[i] = 255;
			}
			else {
				filtered2.getPixels()[i] = 0;
			}
		}

		filtered2.flagImageChanged();

		contours2.findContours(filtered2, 50, GRABBER_WIDTH * GRABBER_HEIGHT / 2, 1, false);
	}
}

void ofApp::draw() {
	if (showVideo) {
		rgbImage.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if (showHSVComponents) {
		hsvImage.draw(0, 0);
		hue.draw(0, 240);
		saturation.draw(320, 240);
		value.draw(640, 240);
	}

	if (showFilter) {
		filtered.draw(0, 480);
		filtered2.draw(320, 480);
	}

	if (showContours) {
		contours.draw(0, 0, ofGetWidth(), ofGetHeight());
		contours2.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofSetColor(ofColor::blue, 100);
	ofFill();
	for (int i = 0; i < contours.blobs.size(); i++) {
		ofDrawCircle(contours.blobs[i].centroid.x * ofGetWidth() / GRABBER_WIDTH,
			contours.blobs[i].centroid.y * ofGetHeight() / GRABBER_HEIGHT,
			20);
	}
	for (int i = 0; i < contours2.blobs.size(); i++) {
		ofDrawCircle(contours2.blobs[i].centroid.x * ofGetWidth() / GRABBER_WIDTH,
			contours2.blobs[i].centroid.y * ofGetHeight() / GRABBER_HEIGHT,
			20);
	}
	ofSetColor(ofColor::white);
}

void ofApp::keyPressed(int key) {
	if (key == 'h') {
		showHSVComponents = !showHSVComponents;
	}
	else if (key == 'v') {
		showVideo = !showVideo;
	}
	else if (key == 'f') {
		showFilter = !showFilter;
	}
	else if (key == 'c') {
		showContours = !showContours;
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0) {
		selectedHue = hue.getPixels()[y * GRABBER_WIDTH + x];
		cout << "Selected 1: " << selectedHue << endl;
	}

	if (button == 2) {
		selectedHue2 = hue.getPixels()[y * GRABBER_WIDTH + x];
		cout << "Selected 2: " << selectedHue2 << endl;
	}
}