#include "Ball.h"
#include "ofApp.h"

Ball::Ball() {
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
}

void Ball::reset() {
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	speed = ofVec2f(ofRandom(-3, 3) * 3 + 2, ofRandom(-1, 1) * 5 + 2);
}

bool Ball::update(int paddleY1, int paddleY2) {
	
	position += speed;

	//Bounch of wall left and right
	if (position.y > ofGetHeight() - BALL_RADIUS || position.y < BALL_RADIUS) {
		speed.y = -speed.y;
	}


	//Red scores a point
	if (position.x > ofGetWidth() - BALL_RADIUS - ofApp::PADDLE_WIDTH) {
		if (position.y >= paddleY2 && position.y <= paddleY2 + ofApp::PADDLE_HEIGHT) {
			float diff = (position.y - paddleY2 - ofApp::PADDLE_HEIGHT / 2) / 30;
			speed.x = -speed.x;
			speed.y += diff;
		}
		else {
			reset();
			return true;
		}

	}
	//Blue Scores a point
	else if (position.x < BALL_RADIUS - ofApp::PADDLE_WIDTH) {
		if (position.y >= paddleY1 && position.y <= paddleY1 + ofApp::PADDLE_HEIGHT) {
			float diff = (position.y - paddleY1 - ofApp::PADDLE_HEIGHT / 2) / 30;
			speed.x = -speed.x;
			speed.y += diff;
		}
		else {
			reset();
			return true;
		}
	}

	return false;
}

void Ball::draw() {
	ofSetColor(ofColor::white);
	ofDrawCircle(position, BALL_RADIUS);
}