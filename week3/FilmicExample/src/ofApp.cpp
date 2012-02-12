#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	
	cameraFilter.setup(ofGetWidth(), ofGetHeight());
	
	shader.load("DOFCloud");	
	focusDistance = 500;
	aperture = .2;
	
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
	
	ofEnableAlphaBlending();
}

void ofApp::update() {
	cameraFilter.setDistortion(ofMap(mouseX, 0, ofGetWidth(), -1, 1, true));
}

void ofApp::draw() {
	ofBackground(0);
	cameraFilter.begin();
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	shader.begin();
	shader.setUniform1f("focusDistance", focusDistance);
	shader.setUniform1f("aperture", aperture);
	glEnable(GL_POINT_SMOOTH); // makes circular points
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);	// allows per-point size
	mesh.draw();
	shader.end();
	cam.end();
	cameraFilter.end();
	
	// these two lines are a bug with 007, but fixed in the develop branch
	// if you're using OF from github, comment out these two lines.
	ofTranslate(0, ofGetHeight());
	ofScale(1, -1, 1);
	
	cameraFilter.draw();
}

void ofApp::keyPressed(int key) {
	focusDistance = mouseX;
	aperture = ofMap(mouseY, 0, ofGetHeight(), 0, 1, true);
}