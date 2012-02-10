#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	int threshold, xyspacing, zspacing;
	float width, height, depth;
	ofEasyCam cam;
	ofMesh mesh;
};
