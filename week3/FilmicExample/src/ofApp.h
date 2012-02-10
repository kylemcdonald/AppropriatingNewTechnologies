#pragma once

#include "ofMain.h"
#include "ofxCameraFilter.h"

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
	ofxCameraFilter cameraFilter;
};
