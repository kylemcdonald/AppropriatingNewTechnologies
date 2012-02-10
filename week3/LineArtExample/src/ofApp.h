#pragma once

#include "ofMain.h"
#include "LineArt.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofEasyCam cam;
	ofMesh mesh;
	ofImage bg;
};
