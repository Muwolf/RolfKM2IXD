#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
//#include "Silhouette.h"

class ofApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	//Camera

	ofVideoPlayer			vidPlayer;
	ofVideoGrabber			grabber;
	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvContourFinder		contourFinder;
	int						thresholdValue;
	bool					bLearnBackground;
	bool					takePhoto;
	bool					drawDebug;

	//Color

	int						red;
	int						green;
	int						blue; 
	int						colorMod; 

	//RGB Led

	int						pinRedLed; 
	int						pinGreenLed; 
	int						pinBlueLed; 

	//Silhouette

	//vector<Silhouette> silhouetteList;
	//Silhouette silhouette; 

	//Arduino

	int						pinAddButton;
	int						pinRedButton;
	int						pinGreenButton;
	int						pinBlueButton;
private:
	ofArduino				arduino;
	void					setupArduino(const int& version);
	void					digitalPinChanged(const int& pin);
};