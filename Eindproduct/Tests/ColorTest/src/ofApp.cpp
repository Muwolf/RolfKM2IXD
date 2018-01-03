#include "ofApp.h"

#define NUMBERCOLORS 6

void ofApp::setup() {
	x = 0;
	y = 0;
	colorR = 0;
	colorG = 0;
	colorB = 0;
	colorMod = 255 / (NUMBERCOLORS - 1);

	for (int b = 0; b < NUMBERCOLORS; b++) {

		colorB = b*colorMod;
		xMod = b*NUMBERCOLORS;
		yMod = b*NUMBERCOLORS;


		for (int r = 0; r < NUMBERCOLORS; r++) {
			x = 0;
			y = r + yMod;
			colorR = r*colorMod;

			colorClass.newColor(NUMBERCOLORS, x, y, colorR, colorG, colorB);
			colorList.push_back(colorClass);

			for (int g = 0; g < NUMBERCOLORS; g++) {
				x = g + xMod;
				y = r;
				colorG = g*colorMod;
				colorClass.newColor(NUMBERCOLORS, x, y, colorR, colorG, colorB);
				colorList.push_back(colorClass);
			}
		}
	}

	ofLog() << "Total Number of Squares: " << colorList.size() << endl;
	ofLog() << "There are suppose to be: " << NUMBERCOLORS * NUMBERCOLORS * NUMBERCOLORS << endl; 
}

void ofApp::update() {

	for (int i = 0; i < colorList.size(); i++) {
		colorList[i].update();
	}
}

void ofApp::draw() {
	for (int i = 0; i < colorList.size(); i++) {
		colorList[i].draw();

	}
}