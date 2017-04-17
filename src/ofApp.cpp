#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	//receive.setup(PORT);

	//sender.setup("192.168.29.147", 12345);
	sender.setup(HOST, PORT);
	kinect.initSensor();
	kinect.initColorStream(640, 480);
	kinect.initSkeletonStream(true);

	kinect.start();
	ofDisableAlphaBlending();

}

//--------------------------------------------------------------
void ofApp::update(){
	/*while (receive.hasWaitingMessages())
	{
		ofxOscMessage m;
		if (m.getAddress() == "/meta/handshake/")
		{
			sender.setup(m.getArgAsString(0), m.getArgAsInt(1)); //IP
		}
	}*/



	kinect.update();

	ofPoint head;
	ofPoint rightHand;
	if (kinect.isNewSkeleton()) {
		auto skeletons = kinect.getSkeletons();
		for (int i = 0; i < skeletons.size(); i++)
		{
			// has a head? probably working ok then :) (turns out if you try to find(..._HEAD) if it doesn't exist, runtime error
			if (skeletons[i].find(NUI_SKELETON_POSITION_HEAD) != skeletons[i].end())
			{
				head = skeletons[i].find(NUI_SKELETON_POSITION_HEAD)->second.getStartPosition();
				/*ofxOscMessage m;	//do not do this - OSC spam causing perf tank?
				m.setAddress("/head/");
				m.addFloatArg(head.x);
				m.addFloatArg(head.y);
				m.addFloatArg(head.z);
				sender.sendMessage(m, false);*/

				rightHand = skeletons[i].find(NUI_SKELETON_POSITION_HAND_RIGHT)->second.getStartPosition();


				headsp = skeletons[i].find(NUI_SKELETON_POSITION_HEAD)->second.getScreenPosition();
				lhsp = skeletons[i].find(NUI_SKELETON_POSITION_HAND_LEFT)->second.getScreenPosition();
				rhsp = skeletons[i].find(NUI_SKELETON_POSITION_HAND_RIGHT)->second.getScreenPosition();
				/*ofxOscMessage msp;	//do not do this - OSC spam causing perf tank?
				msp.setAddress("/head/screenPosition/");
				cout << headsp.x << ", " << headsp.y << endl;
				msp.addFloatArg(headsp.x);
				msp.addFloatArg(headsp.y);
				sender.sendMessage(msp, false);*/
				
			}
		}
	}



	/*ofxOscMessage giveMeHead;
	giveMeHead.setAddress("/head/screenPosition/");
	giveMeHead.addFloatArg(headsp.x);
	giveMeHead.addFloatArg(headsp.y);
	//cout << head << endl;
	//if (frame % 2 == 0)
	//{
		sender.sendMessage(giveMeHead, false);
	//}

	ofxOscMessage giveMeleftHand;
	giveMeleftHand.setAddress("/leftHand/screenPosition/");
	giveMeleftHand.addFloatArg(lhsp.x);
	giveMeleftHand.addFloatArg(lhsp.y);
	//cout << leftHand << endl;
	sender.sendMessage(giveMeleftHand, false);

	ofxOscMessage giveMerightHand;
	giveMerightHand.setAddress("/rightHand/screenPosition/");
	giveMerightHand.addFloatArg(rhsp.x);
	giveMerightHand.addFloatArg(rhsp.y);
	//cout << rightHand << endl;
	sender.sendMessage(giveMerightHand, false);*/


	ofxOscMessage maws;
	maws.setAddress("/head/");
	maws.addFloatArg(head.x);
	maws.addFloatArg(head.y);
	maws.addFloatArg(head.z);
	sender.sendMessage(maws, false);

	/*ofxOscMessage rightmaws;
	rightmaws.setAddress("/rightHand/");
	rightmaws.addFloatArg(rightHand.x);
	rightmaws.addFloatArg(rightHand.y);
	rightmaws.addFloatArg(rightHand.z);
	sender.sendMessage(rightmaws, false);*/

	/*ofxOscMessage headScreenPos;
	headScreenPos.setAddress("/head/screenPosition/");
	headScreenPos.addFloatArg(headsp.x);
	headScreenPos.addFloatArg(headsp.y);
	sender.sendMessage(headScreenPos, false);*/

	frame++;
}

//--------------------------------------------------------------
void ofApp::draw(){

	kinect.draw(0,0);
	ofDrawCircle(headsp, 15);
	//ofDrawCircle(mouseX, mouseY, 15);

	ofPushStyle();
	//ofSetColor(255, 0, 0);
	//ofFpsCounter();
	//ofDrawBitmapString(fps, 0, 480);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
