#pragma once

#define _BALL
#include "ofMain.h"

class Ball
{
public:

	void newBall(float _radius, float _colorR, float _colorG, float _colorB);

	void update();
	void draw();

	float x;
	float y;
	float alpha;
	float radius;
	float colorR;
	float colorG;
	float colorB; 
	ofColor color;


	Ball();

private:

};
