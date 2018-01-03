#pragma once

#include "ofMain.h"
#include "Color.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();		

		float x; 
		float y; 
		float xMod;
		float yMod; 
		float colorR;
		float colorG;
		float colorB; 
		float colorMod; 
		ofColor color; 
 
		vector<Color> colorList; 


		Color colorClass; 
};
