#pragma once

#include "ofMain.h"
#include "OneLiner.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void audioOut(float* input, int n, int channels);
	ofSoundStream soundStream;	
	
	ofShader shader;
	ofFbo fbo;
	ofPixels audioPixels;
	unsigned long time;
	unsigned int rateDivider;
	int curCount;
};
