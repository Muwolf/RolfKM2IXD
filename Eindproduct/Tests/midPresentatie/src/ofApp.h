#pragma once

#include "ofMain.h"
#include "Silhouette.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	vector<Silhouette> shadows;

	Silhouette silhouette;


};
