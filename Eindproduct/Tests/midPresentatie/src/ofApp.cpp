#include "ofApp.h"

void ofApp::setup() {
	ofSetBackgroundColor(255);
}

void ofApp::update() {
	for (int i = 0; i < shadows.size(); i++) {
		shadows[i].update();
		if (shadows[i].color.a <= 0) {
			shadows.erase(shadows.begin() + i);
		}
	}
}

void ofApp::draw() {
	for (int i = 0; i < shadows.size(); i++) {
		shadows[i].draw();
	}
}

void ofApp::keyPressed(int key) {
	if (key == ' ') {
		silhouette.newSilhouette();
		shadows.push_back(silhouette);
	}
}