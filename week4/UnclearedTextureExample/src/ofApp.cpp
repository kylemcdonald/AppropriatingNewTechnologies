#include "ofApp.h"

void ofApp::setup() {
	// each 512x512x3 texture is about .7MB
	// so n = 512 will use about 400MB of texture memory
	int n = 512;
	
	for(int i = 0; i < n; i++) {
		ofTexture cur;
		cur.allocate(512, 512, GL_RGB);
		textures.push_back(cur);
	}
}  

void ofApp::update() {
}

void ofApp::draw() {
	int i = ofMap(mouseX, 0, ofGetWidth(), 0, textures.size() - 1, true);
	textures[i].draw(0, 0);
}