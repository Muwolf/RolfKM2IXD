#pragma once


#include "ofMain.h"

#define BALL_RADIUS 20

class Ball {
	ofPoint position;
	ofVec2f speed;

public:
	Ball();
	void reset();

	bool update(int paddleY1, int paddleY2);
	

	void draw();
};
