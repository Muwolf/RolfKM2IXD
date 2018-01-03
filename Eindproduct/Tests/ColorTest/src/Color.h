#pragma once


#define _COLOR
#include "ofMain.h"
#include "ofMain.h"

class Color
{
public:

	void newColor (float _numberColors, float _x, float _y, float _colorR, float _colorG, float _colorB);
	void update();
	void draw();

	float x;
	float y;
	float colorR; 
	float colorG;
	float numberColors;
	float colorB; 
	float width;
	float height; 
	ofColor color;

	Color();

private:

};
