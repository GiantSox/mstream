#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	addressInput = gui->addTextInput("IP");
	portInput = gui->addTextInput("Port (currently nonfunctional)");
	portInput->setInputType(ofxDatGuiInputType::NUMERIC);
	confirmReceiver = gui->addButton("Confirm Address/Port");

	gui->onTextInputEvent(this, &ofApp::textInputHandler);
	gui->onButtonEvent(this, &ofApp::buttonHandler);


	sender.setup(HOST, PORT);
	kinect.initSensor();
	kinect.initColorStream(640, 480);
	kinect.initSkeletonStream(true);

	kinect.start();
	ofDisableAlphaBlending();

}

void ofApp::textInputHandler(ofxDatGuiTextInputEvent e)
{
	if (e.target == addressInput)
	{
		HOST = e.text;
	}
}

void ofApp::buttonHandler(ofxDatGuiButtonEvent e)
{
	if (e.target == confirmReceiver)
	{
		cout << "sending to " << HOST << ":" << PORT << endl;
		sender.setup(HOST, PORT);
	}
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
	ofPoint leftHand;
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

				leftHand = skeletons[i].find(NUI_SKELETON_POSITION_HAND_LEFT)->second.getStartPosition();
				rightHand = skeletons[i].find(NUI_SKELETON_POSITION_HAND_RIGHT)->second.getStartPosition();

				headsp = skeletons[i].find(NUI_SKELETON_POSITION_HEAD)->second.getScreenPosition();
				lhsp = skeletons[i].find(NUI_SKELETON_POSITION_HAND_LEFT)->second.getScreenPosition();
				rhsp = skeletons[i].find(NUI_SKELETON_POSITION_HAND_RIGHT)->second.getScreenPosition();
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


	ofxOscMessage headMsg;
	headMsg.setAddress("/head/");
	headMsg.addFloatArg(head.x);
	headMsg.addFloatArg(head.y);
	headMsg.addFloatArg(head.z);

	ofxOscMessage leftHandMsg;
	leftHandMsg.setAddress("/leftHand/");
	leftHandMsg.addFloatArg(leftHand.x);
	leftHandMsg.addFloatArg(leftHand.y);
	leftHandMsg.addFloatArg(leftHand.z);

	ofxOscMessage rightHandMsg;
	rightHandMsg.setAddress("/rightHand/");
	rightHandMsg.addFloatArg(rightHand.x);
	rightHandMsg.addFloatArg(rightHand.y);
	rightHandMsg.addFloatArg(rightHand.z);

	ofxOscBundle triBundle;
	triBundle.addMessage(headMsg);
	triBundle.addMessage(leftHandMsg);
	triBundle.addMessage(rightHandMsg);
	sender.sendBundle(triBundle);

}

//--------------------------------------------------------------
void ofApp::draw(){

	kinect.draw(0,0);
	ofDrawCircle(headsp, 15);
	ofDrawCircle(lhsp, 15);
	ofDrawCircle(rhsp, 15);
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
