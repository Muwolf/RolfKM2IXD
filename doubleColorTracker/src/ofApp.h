#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define HUE_MARGIN 5

static const int GRABBER_HEIGHT = 240;
static const int GRABBER_WIDTH = 320;

class ofApp : public ofBaseApp {

public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	void mousePressed(int x, int y, int button);

	ofVideoGrabber grabber;

	ofxCvColorImage rgbImage;
	ofxCvColorImage hsvImage;

	ofxCvGrayscaleImage hue;
	ofxCvGrayscaleImage saturation;
	ofxCvGrayscaleImage value;

	ofxCvGrayscaleImage filtered;
	ofxCvGrayscaleImage filtered2;

	ofxCvContourFinder contours;
	ofxCvContourFinder contours2;

	int selectedHue;
	int selectedHue2;

	bool showHSVComponents = true;
	bool showFilter = true;
	bool showContours = true;
	bool showVideo = true;

};