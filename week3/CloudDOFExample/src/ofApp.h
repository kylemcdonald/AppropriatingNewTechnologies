#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofEasyCam cam;
	ofMesh mesh;
	ofShader shader;
	float focusDistance, aperture;
};
