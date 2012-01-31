#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){

	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	tex.allocate(300,300, GL_RGBA);
	
	ofSetFrameRate(30);

}

//--------------------------------------------------------------
void testApp::update(){
	
	int w = 300;
	int h = 300;
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		
		unsigned char r = data[i*4];
		data[i*4] = data[i*4+2];
		data[i*4+2] = r;
	}
	
	
	if (data!= NULL) tex.loadData(data, 300, 300, GL_RGBA);
	//cout << imageBelowWindow()[0] << endl;
	

}

//--------------------------------------------------------------
void testApp::draw(){
	tex.draw(0,0, ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}