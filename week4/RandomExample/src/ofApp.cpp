#include "ofApp.h"

// https://en.wikipedia.org/wiki/Linear_feedback_shift_register#Galois_LFSRs
unsigned int lfsr = 1;
unsigned int galois() {
  lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xD0000001u);
	return lfsr;
}

void ofApp::setup() {
	img.allocate(512, 512, OF_IMAGE_COLOR);
}  

void ofApp::update() {
	unsigned char* pixels = img.getPixels();
	int n = 3 * img.getWidth() * img.getHeight();
	for(int i = 0; i < n; i++) {
		int cur = galois();
		pixels[i] = cur;
	}
	img.update();
}

void ofApp::draw() {
	img.draw(0, 0);
}