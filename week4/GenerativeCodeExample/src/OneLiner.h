#pragma once

class OneLiner {
private:
	static string randomOperator() {
		int c = ofRandom(148);
		if(c < 1) return "/";
		else if(c < 2) return "%";
		else if(c < 3) return "<<";
		else if(c < 4) return "^";
		else if(c < 11) return "+";
		else if(c < 19) return "-";
		else if(c < 41) return "|";
		else if(c < 64) return "*";
		else if(c < 92) return "&";
		return ">>";
	}
	static string randomQuantity() {
		int x;
		if(ofRandom(1) < .75) {
			x = 1 + (int) ofRandom(16);
		} else {
			int bases[5] = {24, 48, 64, 128, 255};
			x = bases[(int) ofRandom(5)];
			if(ofRandom(1) < .25) {
				x += ofRandom(-8, +8);
			}
		}
		return ofToString(x);
	}
	static string randomNode(bool useT, int levels) {
		levels--;
		if(levels > 0 && ofRandom(1) < .9) {
			if(ofRandom(1) < .1) {
				return "(" + randomNode(true, levels) + ">0?" + randomNode(true, levels) + ":" + randomNode(false, levels) + ")";
			} else {
				bool curUseT = ofRandom(1) < .8;
				return "(" + randomNode(curUseT, levels) + randomOperator() + randomNode(!curUseT, levels) + ")";
			}
		} else {
			if(useT) {
				return "t";
			} else {
				return randomQuantity();
			}
		}
	}
public:
	static string build() {
		return randomNode(true, 6);
	}
};