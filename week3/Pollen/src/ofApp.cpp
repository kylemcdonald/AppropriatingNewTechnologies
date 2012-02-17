#include "ofApp.h"

ofVec2f ofApp::getField(ofVec2f position) {
	float normx = ofNormalize(position.x, 0, width);
	float normy = ofNormalize(position.y, 0, height);
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
}

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	
	width = ofGetWidth();
	height = ofGetHeight();
	nPoints = 4096; // points to draw
	complexity = 6; // wind complexity
	maxMass = .8; // max pollen mass
	timeSpeed = .02; // wind variation speed
	phase = TWO_PI; // separate u-noise from v-noise
	windSpeed = 40; // wind vector magnitude for debug
	step = 10; // spatial sampling rate for debug
	debugMode = false;
	
  points.resize(nPoints);
  pollenMass.resize(nPoints);
  for(int i = 0; i < nPoints; i++) {
    points[i] = ofVec2f(ofRandom(0, width), ofRandom(0, height));
    pollenMass[i] = ofRandom(0, maxMass);
  }
  ofBackground(255);
	mesh.clear();
}

void ofApp::update() {
  t = ofGetFrameNum() * timeSpeed;
} 

void ofApp::draw() { 	
  if(debugMode) {
    ofBackground(255);
    ofSetColor(0);
    float s = windSpeed;
    for(int i = 0; i < width; i += step) {
      for(int j = 0; j < height; j += step) {
				ofVec2f field = getField(ofVec2f(i, j));
        ofPushMatrix();
        ofTranslate(i, j);
				ofSetColor(0);
        ofLine(0, 0, ofLerp(-windSpeed, windSpeed, field.x), ofLerp(-windSpeed, windSpeed, field.y));
        ofPopMatrix();
      }
    }
  }
	
	//ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
  for(int i = 0; i < nPoints; i++) {
		float& x = points[i].x, y = points[i].y;
		ofVec2f field = getField(points[i]);
    float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass[i];
    x += ofLerp(-speed, speed, field.x);
    y += ofLerp(-speed, speed, field.y);
		
    if(x < 0 || x > width || y < 0 || y > height) {
      x = ofRandom(0, width);
      y = ofRandom(0, height);
    }
		
    if(debugMode) {
			ofSetColor(255, 0, 0);
      ofCircle(x, y, 3);
    } else {
      mesh.addVertex(ofVec2f(x, y));
		}
		
    points[i].x = x;
    points[i].y = y;
  }
	if(!debugMode) {
    ofSetColor(0, 10);
		mesh.draw();
	}
}

void ofApp::mousePressed(int x, int y, int button) {
  setup();
}

void ofApp::keyPressed(int key) {
  debugMode = !debugMode;
  ofBackground(255);
}
