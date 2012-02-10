#include "ofApp.h"

// save http://i.imgur.com/ym71g.gif as data/body.gif

void ofApp::setup() {
	ofSetVerticalSync(true);
	mesh.setMode(OF_PRIMITIVE_POINTS);

	xyspacing = 8;
	zspacing = 8;
	threshold = 100;
	
	ofVideoPlayer body;
	body.loadMovie("body.gif");
	int n = body.getTotalNumFrames();
	for(int i = 0; i < n; i++) {
		// load and save the current frame
		body.setFrame(i);
		// process each slice
		ofPixels& pix = body.getPixelsRef();
		for(int y = 0; y < pix.getHeight(); y += xyspacing) {
			for(int x = 0; x < pix.getWidth(); x += xyspacing) {
				ofColor color = pix.getColor(x, y);
				if(color.getBrightness() > threshold) {
					float z = i * zspacing;
					ofVec3f pos(x, y, z);
					mesh.addVertex(pos);
					mesh.addColor(color);
				}
			}
		}
	}
	
	width = body.getWidth();
	height = body.getHeight();
	depth = n * zspacing;
	
	glEnable(GL_DEPTH_TEST);
}

void ofApp::update() {
}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofTranslate(-width / 2, -height / 2, -depth / 2);
	if(ofGetMousePressed()) {
		mesh.draw();
	} else {
		for(int i = 0; i < mesh.getNumVertices(); i++) {
			ofSetColor(mesh.getColor(i));
			ofBox(mesh.getVertex(i), zspacing);
		}
	}
	cam.end();
}
