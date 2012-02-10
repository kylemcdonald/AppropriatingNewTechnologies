#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofImage img;
	img.loadImage("linzer.png");
	mesh.setMode(OF_PRIMITIVE_POINTS);
	for(int y = 0; y < img.getHeight(); y++) {
		for(int x = 0; x < img.getWidth(); x++) {
			ofColor cur = img.getColor(x, y);
			if(cur.a > 0) {
				// the alpha value encodes depth, let's remap it to a good depth range
				float z = ofMap(cur.a, 0, 255, -480, 480);
				cur.a = 255;
				mesh.addColor(cur);
				ofVec3f pos(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
				mesh.addVertex(pos);
			}
		}
	}
	
	// even points can overlap with each other, let's avoid that
	glEnable(GL_DEPTH_TEST);
	
	// make the points bigger, otherwise it's hard to see them
	glPointSize(4);
}

void ofApp::update() {

}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	mesh.draw();
	cam.end();
}