#include "ofApp.h"

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(c);
	mesh.addVertex(b);
	mesh.addVertex(a);
}

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

ofVec3f getVertexFromImg(ofImage& img, int x, int y) {
	ofColor color = img.getColor(x, y);
	if(color.a > 0) {
		float z = ofMap(color.a, 0, 255, -480, 480);
		return ofVec3f(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
	} else {
		return ofVec3f(0, 0, 0);
	}
}

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofImage img;
	img.loadImage("linzer.png");
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	int skip = 4;	
	int width = img.getWidth();
	int height = img.getHeight();
	ofVec3f zero(0, 0, 0);
	for(int y = 0; y < height - skip; y += skip) {
		for(int x = 0; x < width - skip; x += skip) {
			ofVec3f nw = getVertexFromImg(img, x, y);
			ofVec3f ne = getVertexFromImg(img, x + skip, y);
			ofVec3f sw = getVertexFromImg(img, x, y + skip);
			ofVec3f se = getVertexFromImg(img, x + skip, y + skip);
			if(nw != zero && ne != zero && sw != zero && se != zero) {
				addFace(mesh, nw, ne, se, sw);
			}
		}
	}
	
	// add some random triangles
	for(int i = 0; i < 20; i++) {
		ofVec3f center(ofRandomf(), ofRandomf(), ofRandomf());
		center *= ofGetWidth() / 2;
		float scale = ofRandom(10, 100);
		ofVec3f nw = center + ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()) * scale;
		ofVec3f ne = center + ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()) * scale;
		ofVec3f sw = center + ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()) * scale;
		addFace(mesh, nw, ne, sw);
	}
	
	bg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	for(int y = 0; y < ofGetHeight(); y++) {
		for(int x = 0; x < ofGetWidth(); x++) {
			float dist = ofDist(x, y, ofGetWidth() / 2, ofGetHeight() / 2);
			float brightness = ofMap(dist, 0, ofGetWidth() / 2, 255, 128);
			bg.setColor(x, y, ofColor(ofClamp(brightness, 0, 255)));
		}
	}
	bg.update();
}

void ofApp::update() {
	
}

void ofApp::draw() {
	ofSetColor(255);
	bg.draw(0, 0);
	
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	
	ofSetColor(128);
	ofEnableSmoothing();
	ofSetLineWidth(2);
	LineArt::draw(mesh, true, ofColor::white);
	
	cam.end();
}