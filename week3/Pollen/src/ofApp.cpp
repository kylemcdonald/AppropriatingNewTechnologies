#include "ofApp.h"

int nPoints = 4096; // points to draw
float complexity = 6; // wind complexity
float maxMass = .8; // max pollen mass
float timeSpeed = .02; // wind variation speed
float phase = TWO_PI; // separate u-noise from v-noise
 
float windSpeed = 40; // wind vector magnitude for debug
int step = 10; // spatial sampling rate for debug
 
vector<float> pollenMass;
vector<ofVec2f> points;
 
bool debugMode = false;

float width, height;

ofMesh mesh;
 
void ofApp::setup() {
	ofSetVerticalSync(true);
	//ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
	width = ofGetWidth();
	height = ofGetHeight();
	
  points.resize(nPoints);
  pollenMass.resize(nPoints);
  for(int i = 0; i < nPoints; i++) {
    points[i] = ofVec2f(ofRandom(0, width), ofRandom(0, height));
    pollenMass[i] = ofRandom(0, maxMass);
  }
  //noiseDetail(14);
  ofBackground(255);
}

void ofApp::update() {
} 

void ofApp::draw() { 
  float t = ofGetFrameNum() * timeSpeed;
   
  if(debugMode) {
    ofBackground(255);
    ofSetColor(0);
    float s = windSpeed;
    for(int i = 0; i < width; i += step) {
      for(int j = 0; j < height; j += step) {
        float normx = ofMap(i, 0, width, 0, 1);
        float normy = ofMap(j, 0, height, 0, 1);
        float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
        float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
        ofPushMatrix();
        ofTranslate(i, j);
        ofLine(0, 0, ofLerp(-windSpeed, windSpeed, u), ofLerp(-windSpeed, windSpeed, v));
        ofPopMatrix();
      }
    }   
    ofSetColor(255, 0, 0);
  } else {
    ofSetColor(0, 10);
  }
	
	//ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
  for(int i = 0; i < nPoints; i++) {
    float x = points[i][0];
    float y = points[i][1];
     
    float normx = ofNormalize(x, 0, width);
    float normy = ofNormalize(y, 0, height);
    float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
    float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
    float speed = (1 + ofNoise(t, u, v)) / pollenMass[i];
    x += ofLerp(-speed, speed, u);
    y += ofLerp(-speed, speed, v);
     
    if(x < 0 || x > width || y < 0 || y > height) {
      x = ofRandom(0, width);
      y = ofRandom(0, height);
    }
     
    if(debugMode) {
      ofCircle(x, y, 1);
    } else
      mesh.addVertex(ofVec2f(x, y));
       
    points[i].x = x;
    points[i].y = y;
  }
	mesh.draw();
}
 
void ofApp::mousePressed(int x, int y, int button) {
  setup();
}
 
void ofApp::keyPressed(int key) {
  debugMode = !debugMode;
  ofBackground(255);
}
