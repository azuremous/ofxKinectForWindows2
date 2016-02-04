#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodyIndexSource();
	kinect.initBodySource();

	gui.init();

	//setup a gui panel for every kinect source
	auto sources = kinect.getSources();
	for(auto source : sources) {
		auto sourceWithTexture = dynamic_pointer_cast<ofBaseHasTexture>(source);
		if (sourceWithTexture) {
			auto panel = gui.add(sourceWithTexture->getTexture(), source->getTypeName());

			//if it's the colour panel, let's do something special by writing some info on top
			auto colorSource = dynamic_pointer_cast<ofxKFW2::Source::Color>(source);
			if (colorSource) {
				panel->onDraw += [colorSource] (ofxCvGui::DrawArguments &) {
					stringstream message;
					message << "Exposure : " << colorSource->getExposure() << "us" << endl;
					message << "FrameInterval : " << colorSource->getFrameInterval() << "us" << endl;
					message << "Gain : " << colorSource->getGain() << endl;
					message << "Gamma : " << colorSource->getGamma() << endl;
					ofxCvGui::Utils::drawText(message.str(), 20, 60);
				};
			}

			//if it's the depth panel, set some scaling
			auto depthSource = dynamic_pointer_cast<ofxKFW2::Source::Depth>(source);
			if (depthSource) {
				auto style = panel->getStyle();
				style.rangeMaximum = 0.25f;
				//panel->setStyle(style);
			}
		}
	}

	auto worldView = gui.addWorld("World");
	worldView->onDrawWorld += [this] (ofCamera &) {
		this->kinect.drawWorld();
	};

	//if we press the 'c' key on the World panel, then toggle the camera's cursor. This works best when you fullscreen that panel
	worldView->onKeyboard += [this, worldView] (ofxCvGui::KeyboardArguments & args) {
		if (args.action == ofxCvGui::KeyboardArguments::Action::Pressed && args.key =='c') {
			worldView->getCamera().toggleCursorDrawEnabled();
		}
	};
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	mesh = kinect.getDepthSource()->getMesh(true, ofxKinectForWindows2::Source::Depth::PointCloudOptions::TextureCoordinates::ColorCamera);
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
