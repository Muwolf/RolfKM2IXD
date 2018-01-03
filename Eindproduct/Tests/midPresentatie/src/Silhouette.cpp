#include "Silhouette.h"

Silhouette::Silhouette() {};



void Silhouette::newSilhouette() {
	radius = ofGetHeight() / 4;

	x = ofRandom(radius, ofGetWidth() - radius);
	y = ofGetHeight() - radius;
	alpha = 255;
}

void Silhouette::update() {
	alpha = alpha - 0.2;
	color.set(0, 0, 0, alpha);
}

void Silhouette::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, radius);
}



Silhouette::~Silhouette()
{
}
