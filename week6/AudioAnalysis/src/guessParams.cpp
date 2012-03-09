#include "guessParams.h"

vector<double> sorted;
const float minMaxRatio = .05;

void guessParams(vector<double>& raw, double& frequency, double& amplitude, double& phaseOffset, double& dcOffset, double& shape) {
	// initial low pass to get rid of any shot noise that might disrupt the zero crossing algorithm
	Mat rawMat = Mat(1, raw.size(), CV_64FC1, &raw[0]);
	GaussianBlur(rawMat, rawMat, cv::Size(3, 3), 0, 0);
	
	// sort and average the two ends to get min and max
	vector<double> sorted = raw;
	ofSort(sorted);
	float minMaxRatio = .1;
	int minMaxRange = minMaxRatio * sorted.size();
	double avgMin = 0;
	double avgMax = 0;
	for(int i = 0; i < minMaxRange; i++) {
		avgMin += sorted[i];
		avgMax += sorted[sorted.size() - 1 - i];
	}
	avgMin /= minMaxRange;
	avgMax /= minMaxRange;
	
	amplitude = (avgMax - avgMin) / 2;
	dcOffset = (avgMax + avgMin) / 2;
	
	// find zeros
	vector<int> zeros;
	bool rising;
	int minHalfWavelength = 1; // avoids double-triggering from noise
	for(int i = 1; i < raw.size(); i++) {
		double prev = raw[i - 1];
		double cur = raw[i];
		if(cur >= dcOffset && prev < dcOffset) {
			if(zeros.size() == 0) {
				rising = true;
			}
			zeros.push_back(i);
			i += minHalfWavelength;
		}
		if(cur <= dcOffset && prev > dcOffset) {
			if(zeros.size() == 0) {
				rising = false;
			}
			zeros.push_back(i);
			i += minHalfWavelength;
		}
	}
	
	if(zeros.size() < 3) {
		frequency = 0;
		phaseOffset = 0;
		shape = 0;
		return;
	}
	
	/*
	 // make it odd, to ensure there is an integer number of waves
	 if(zeros.size() % 2 == 0) {
	 zeros.resize(zeros.size() - 1);
	 }
	 
	 // linearly interpolate the zeros' position
	 int fronti = zeros.front();
	 int backi = zeros.back();
	 double front = ofMap(dcOffset, raw[fronti - 1], raw[fronti], fronti - 1, fronti);
	 double back = ofMap(dcOffset, raw[backi - 1], raw[backi], backi - 1, backi);
	 double wavelength = 2 * (back - front) / (zeros.size() - 1);
	 */
	
	// better technique using the average of the middle values
	vector<double> refinedZeros;
	refinedZeros.resize(zeros.size());
	
	for(int i = 0; i < refinedZeros.size(); i++) {
		int start = zeros[i];
		refinedZeros[i] = ofMap(dcOffset, raw[start - 1], raw[start], start - 1, start);
	}
	vector<double> wavelengths;
	wavelengths.resize(refinedZeros.size() - 2);
	for(int i = 0; i < wavelengths.size(); i++) {
		wavelengths[i] = refinedZeros[i + 2] - refinedZeros[i];
	}
	ofSort(wavelengths);
	float wavelengthsIgnore = .1;
	int wavelengthsStart = wavelengths.size() * wavelengthsIgnore;
	int wavelengthsStop = wavelengths.size() * (1 - wavelengthsIgnore);
	double avgWavelength = 0;
	for(int i = wavelengthsStart; i < wavelengthsStop; i++) {
		avgWavelength += wavelengths[i];
	}
	double wavelength = avgWavelength / (wavelengthsStop - wavelengthsStart);
	
	// guess based on first two zeros and wavelength
	// this is the most naive portion of the guessing stage
	frequency = 1 / wavelength;
	phaseOffset = (zeros[0] + zeros[1]) / 2 + (rising ? -wavelength / 4 : wavelength / 4);
	phaseOffset = -phaseOffset;
	
	// another technique for wavelength
	// for every point along the wave, find the next point that matches that value + derivative sign
	// then throw out all the outliers
	
	int wavelengthRange = 2;
	int n = raw.size() - 1 - (wavelength + wavelengthRange);
	double ignoreEdges = .2;
	wavelengths.clear();
	for(int i = 1; i < n; i++) {
		double prevFront = raw[i - 1];
		double curFront = raw[i];
		bool risingFront = curFront > prevFront;
		
		double curFrontNorm = ofMap(curFront, avgMin, avgMax, -1, 1);
		if(curFrontNorm < ignoreEdges && curFrontNorm > -ignoreEdges) {
			
			for(int j = -wavelengthRange; j <= wavelengthRange; j++) {
				int k = i + (int) wavelength + j;
				
				double prevBack = raw[k - 1];
				double curBack = raw[k];
				
				if(risingFront && prevBack < curFront && curBack >= curFront) {
					double back = ofMap(curFront, prevBack, curBack, k - 1, k);
					wavelengths.push_back(back - i);
				} else if(!risingFront && prevBack > curFront && curBack <= curFront) {
					double back = ofMap(curFront, prevBack, curBack, k - 1, k);
					wavelengths.push_back(back - i);
				}
			}
		}
	}
	avgWavelength = 0;
	wavelengthsStart = wavelengths.size() * wavelengthsIgnore;
	wavelengthsStop = wavelengths.size() * (1 - wavelengthsIgnore);
	for(int i = wavelengthsStart; i < wavelengthsStop; i++) {
		avgWavelength += wavelengths[i];
	}
	wavelength = avgWavelength / (wavelengthsStop - wavelengthsStart);	
	
	// using subpixel autocorrelation kind of helps but it's really expensive
	/*
	 double minWavelength = wavelength - .5;
	 int resolution = 16;
	 double bestAutocorrelation;
	 double bestWavelength;
	 for(int i = 0; i < resolution; i++) {
	 double curWavelength = minWavelength + (double) i / resolution;
	 double curAutocorrelation = getSubpixelAutocorrelation(raw, curWavelength, resolution);
	 if(i == 0 || curAutocorrelation < bestAutocorrelation) {
	 bestAutocorrelation = curAutocorrelation;
	 bestWavelength = curWavelength;
	 }
	 }
	 wavelength = bestWavelength;
	 */
	
	float avg = 0;
	for(int i = 0; i < raw.size(); i++) {
		avg += ofMap(raw[i], avgMin, avgMax, 0, 1);
	}
	avg /= raw.size();
	// integral of sin(x)^p from 0 to 2*pi is not really easy...
	// but it's approximately f(x) = -.17598 * ln(x) + .50434 with R=.99
	// so x = exp((f(x) - .50434) / -.17598)
	shape = exp((avg - .50434) / -.17598);
}

void guessPhase(vector<double>& row, double wavelength, double& phase) {
	Mat rowMat = Mat(1, row.size(), CV_64FC1, &row[0]);
	GaussianBlur(rowMat, rowMat, cv::Size(21, 21), 0, 0);
	
	// sort and average the two ends to get min and max
	sorted.resize(row.size());
	sorted = row;
	ofSort(sorted);
	int minMaxRange = minMaxRatio * sorted.size();
	float avgMin = 0;
	float avgMax = 0;
	for(int i = 0; i < minMaxRange; i++) {
		avgMin += sorted[i];
		avgMax += sorted[sorted.size() - 1 - i];
	}
	avgMin /= minMaxRange;
	avgMax /= minMaxRange;
	
	float amplitude = (avgMax - avgMin) / 2;
	float dcOffset = (avgMax + avgMin) / 2;
	
	ofVec2f avg;
	for(int x = 0; x < row.size(); x++) {
		float cur = ofMap(row[x], avgMin, avgMax, -1, 1, true);
		if(x > 1) {
			float curPhase = row[x] > row[x - 1] ? asin(cur) : PI - asin(cur);
			float basePhase = fmodf(x, wavelength) * TWO_PI / wavelength;
			curPhase -= basePhase;
			avg.x += cos(curPhase);
			avg.y += sin(curPhase);
		}
	}
	phase = atan2f(avg.y, avg.x);
}
