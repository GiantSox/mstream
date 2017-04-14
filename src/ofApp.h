#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxKinectCommonBridge.h"

#define HOST "192.168.29.202"
//#define HOST "localhost"
//#define HOST "192.168.29.147"
#define PORT 12345


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOscReceiver receive;

		ofxOscSender sender;
		ofxKinectCommonBridge kinect;
		ofPoint headsp;
		ofPoint lhsp;
		ofPoint rhsp;

		int frame = 0;
};
