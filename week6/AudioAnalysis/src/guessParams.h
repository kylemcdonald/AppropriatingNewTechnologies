#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

void guessParams(vector<double>& raw, double& frequency, double& amplitude, double& phaseOffset, double& dcOffset, double& shape);

void guessPhase(vector<double>& row, double wavelength, double& phase);