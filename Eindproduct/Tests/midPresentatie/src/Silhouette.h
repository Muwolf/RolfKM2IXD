#pragma once

#define	_SILHOUETTE
#include "ofMain.h"

class Silhouette
{
public:
	void newSilhouette();
	void update(); 
	void draw(); 

	float radius; 
	float x; 
	float y; 
	ofColor color; 
	float alpha; 

	ofImage image; 

	Silhouette();
	~Silhouette();
};

