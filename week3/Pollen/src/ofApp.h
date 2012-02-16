#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVec2f getField(ofVec2f position);
	
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	
	ofEasyCam cam;
	vector<float> pollenMass;
	vector<ofVec2f> points;
	float width, height;
	ofMesh mesh;
	float t;
	
	int nPoints; // points to draw
	float complexity; // wind complexity
	float maxMass; // max pollen mass
	float timeSpeed; // wind variation speed
	float phase; // separate u-noise from v-noise
	float windSpeed; // wind vector magnitude for debug
	int step; // spatial sampling rate for debug
	bool debugMode;
};
