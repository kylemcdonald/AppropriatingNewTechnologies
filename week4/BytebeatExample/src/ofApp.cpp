#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(15);
	shader.setup("oneliner");
	soundStream.setup(this, 2, 0, 48000, 256, 1);
	fbo.allocate(512, 512);
	time = 0;
	rateDivider = 8;
	curCount = 0;
}

void ofApp::update() {
}

void ofApp::draw() {
	ofSetColor(255);
	
	fbo.begin();
	shader.begin();
	ofFill();
	ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
	shader.end();
	fbo.end();
	
	fbo.draw(0, 0);
	
	fbo.readToPixels(audioPixels);
	
	ofSetColor(255, 0, 0);
	int y = time / (rateDivider * ofGetWidth());
	ofLine(0, y, ofGetWidth(), y);
}


void ofApp::audioOut(float* input, int n, int channels) {
	unsigned char* pixels = audioPixels.getPixels();
	int wh = audioPixels.getWidth() * audioPixels.getHeight();
	int cwh = audioPixels.getNumChannels() * wh;
	if(cwh > 0) {
		for(int i = 0; i < n; i++) {
			int curTime = (time / rateDivider) % wh;
			int curPixel = 4 * curTime;
			for(int j = 0; j < channels; j++) {
				int cur = pixels[curPixel + j];
				input[i * channels + j] = cur / 128. - 1.;
				input[i * channels + j] *= .05;
			}
			time++;
		}
	}
}