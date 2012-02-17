#include "ofApp.h"

void ofApp::setup() {	
	ofSetVerticalSync(true);
	zoomed.allocate(16, 9, OF_IMAGE_COLOR);
	dumpMemory();
}  

void ofApp::update() {
}

void ofApp::draw() {
	ofSetColor(255);
	img.draw(0, 0);
	
	int offset = 3 * (mouseY * img.getWidth() + mouseX);
	unsigned char* pixels = img.getPixels();
	zoomed.setFromPixels(pixels + offset, 16, 9, OF_IMAGE_COLOR);
	zoomed.update();
	ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
	zoomed.draw(10, 10, 320, 180);
}

void ofApp::dumpMemory() {
	int offset = ofRandom(0x0000, 0xffff); // some 32-bit address
	unsigned char* data = (unsigned char*) offset;
	img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	img.setFromPixels(data, img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);
	img.update();
}