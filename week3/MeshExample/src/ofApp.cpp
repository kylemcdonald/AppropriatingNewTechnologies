#include "ofApp.h"

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
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
	int skip = 5;	
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
	
	// even points can overlap with each other, let's avoid that
	glEnable(GL_DEPTH_TEST);
}

void ofApp::update() {
	
}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	mesh.drawWireframe();
	cam.end();
}