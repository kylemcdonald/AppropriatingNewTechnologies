#include "ofApp.h"

// bunny comes from http://graphics.stanford.edu/data/3Dscanrep/
// specifically ftp://graphics.stanford.edu/pub/3Dscanrep/bunny.tar.gz

void ofApp::setup() {
	// otherwise the app will run too fast
	ofSetVerticalSync(true);
	
	// assimp can load all kinds of formats, and supports texture mapping and
	// even animations. use getMesh(0) to get a mesh from assimp. if you have
	// a bunch of meshes inside your 3d model file, change 0 to something else.
	ofxAssimpModelLoader loader;
	loader.loadModel("bun_zipper.ply");
	center = loader.getSceneCenter();
	mesh = loader.getMesh(0);
	
	// when you scale things to make them bigger or smaller, this also scales
	// their normals. because the light is calculated using the normal, this
	// will change how bright the surface is. since we don't want this, we 
	// ask opengl to normalize the normals for us before it does the lighting
	// calculations.
	glEnable(GL_NORMALIZE);
	
	// when we're drawing a 3d model that has faces, we want to make sure that
	// things obscure each other. normally when you draw 2d it's the opposite:
	// you want whatever the most recent thing you've drawn to be the thing in
	// front.
	glEnable(GL_DEPTH_TEST);
	
	// in openFrameworks you enable lighting by creating and enabling a light
	light.enable();
}

void ofApp::update() {
}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	float s = 2400;
	ofScale(s,s,s);
	ofTranslate(-center.x, -center.y, -center.z);
	mesh.draw();
	cam.end();
}
