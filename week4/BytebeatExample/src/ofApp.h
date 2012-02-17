#pragma once

#include "ofMain.h"
#include "ofAutoShader.h"

// some examples
// (t*((t>>12|t>>8)&63&t>>4));// viznut-0
// (t*((t>>9|t>>13)&25&t>>6);}// visy-0
// ((t*(t>>8*(t>>15|t>>8)&(20|(t>>19)*5>>t|t>>3))));// visy-1
// (t*(t>>((t>>9|t>>8))&63&t>>4));// visy-2
// ((t*(t>>5|t>>8))>>(t>>16));// tejeez-0
// (t*(t>>11&t>>8&123&t>>3));// tejeez-1
// (((-t&4095)*(255&t*(t&t>>13))>>12)+(127&t*(234&t>>8&t>>3)>>(3&t>>14)));// tejeez-2
// ((t>>6|t|t>>(t>>16))*10+((t>>11)&7), viznut);
// (v=(v>>1)+(v>>4)+t*(((t>>16)|(t>>6))&(69&(t>>9))), pyryp);
// ((t|(t>>9|t>>7))*t&(t>>11|t>>9), red-);
// (t*5&(t>>7)|t*3&(t*4>>10), miiro);
// ((t>>7|t|t>>6)*10+4*(t&t>>13|t>>6), viznut);
// (((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t)), skurk);
// (((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6), xpansive);
	
class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void audioOut(float* input, int n, int channels);
	ofSoundStream soundStream;	
	
	ofAutoShader shader;
	ofFbo fbo;
	ofPixels audioPixels;
	unsigned long time;
	unsigned int rateDivider;
	int curCount;
};
