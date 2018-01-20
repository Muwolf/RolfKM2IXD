#pragma once
#include "ofMain.h"
class Silhouette 
	{
public:

	void					newSilhouette(vector<ofPoint> _shape, float _colorR, float _colorG, float _colorB);

	float					red;
	float					green; 
	float					blue; 
	vector<ofPoint>			shape;
	float					alpha; 

	void					update();
	void					draw();

	Silhouette();
};

