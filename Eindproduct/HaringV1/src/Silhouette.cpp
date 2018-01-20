#include "Silhouette.h"
#define DECAY 0.01

void Silhouette::newSilhouette(vector<ofPoint> _shape, float _colorR, float _colorG, float _colorB) {
	shape = _shape; 
	red = _colorR;
	green = _colorG;
	blue = _colorB; 
	alpha = 255; 
}

void Silhouette::update() {
	//Decay over time. 
	//Op dit moment is het -0.01 per frame, met 30Fps duurt het 14 minuten en 10 seconden om te verdwijnen.
	//Om de afbeelding over 12 uur te laten verdwijnen zet je de decay op 0,0002
	alpha -= DECAY; 
}

void Silhouette::draw() {
	
	ofBeginShape();
	for (int i = 0; i < shape.size(); i++) {
		ofSetColor(red, green, blue, alpha);
		ofVertex(shape[i]);

	}
	ofEndShape(true);
}



Silhouette::Silhouette()
{
}


