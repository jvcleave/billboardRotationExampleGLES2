#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);
	//ofSetVerticalSync(true);
	hasMouse = false;
	previousX = ofGetWidth()/2;
	previousY = ofGetHeight()/2;
	currentX = 0;
	currentY = 0;
	// billboard particles
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		ofVec3f point;
		
		
		point.x = ofRandomWidth();
		point.y = ofRandomHeight();
		pos.push_back(point);
		vel[i].x = ofRandomf();
		vel[i].y = ofRandomf();
		home[i] = pos[i];
		pointSizes[i] = ofNextPow2(ofRandom(2, 40));
		rotations[i] = ofRandom(0, 360);
	}
	
	mesh.setUsage(GL_DYNAMIC_DRAW);
	mesh.addVertices(pos);
	shader.load("BillboardRotation.vert", "BillboardRotation.frag", "");
	
	ofDisableArbTex();
	texture.loadImage("snow.png");
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update() {
	ofVec2f mouse;
	ofVec2f mouseVec;
	if (!hasMouse) 
	{
		previousX = currentX;
		previousY = currentY;
		
		currentX+=30;
		if (currentX>ofGetWidth()) {
			currentX = ofRandomWidth();
		}
		
		currentY+=30;
		if (currentY>ofGetHeight()) {
			currentY = ofRandomHeight();
		}
		mouse.set(currentX, currentY);
		mouseVec.set(previousX-currentX, previousY-currentY);
	}else {
		mouse.set(ofGetMouseX(), ofGetMouseY());
		mouseVec.set(ofGetPreviousMouseX()-ofGetMouseX(), ofGetPreviousMouseY()-ofGetMouseY());
	}

	mouseVec.limit(10.0);
	
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		ofSeedRandom(i);
		ofVec3f &point = mesh.getVertices()[i];
		
		if(mouse.distance(point) < ofRandom(100, 200)) {
			vel[i] -= mouseVec; 
		}
		
		point += vel[i];
		vel[i] *= 0.84f;
		
		if(point.x < 0) point.x = ofGetWidth();
		if(point.x > ofGetWidth()) point.x = 0;
		if(point.y < 0) point.y = ofGetHeight();
		if(point.y > ofGetHeight()) point.y = 0;
		
		ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);
		ofVec2f frc = home[i] - point;
		if(frc.length() > 20.0) {
			frc.normalize();
			frc *= 0.84;
			vel[i] += frc;
		}
		
		// get the 2d heading
		float angle = (float)atan2(-vel[i].y, vel[i].x) + PI;
		rotations[i] = (angle * -1.0);
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	
	//ofSetColor(255);
	
	ofEnablePointSprites();
	shader.begin();
	
	// we are getting the location of the point size attribute
	// we then set the pointSizes to the vertex attritbute
	// we then bind and then enable
	int pointAttLoc = shader.getAttributeLocation("pointSize");
	glVertexAttribPointer(pointAttLoc, 1, GL_FLOAT, false, 0, pointSizes);
	glBindAttribLocation(shader.getProgram(), pointAttLoc, "pointSize");
	glEnableVertexAttribArray(pointAttLoc);
	
	// rotate the snow based on the velocity
	int angleLoc = shader.getAttributeLocation("angle");
	glVertexAttribPointer(angleLoc, 1, GL_FLOAT, false, 0, rotations);
	glBindAttribLocation(shader.getProgram(), angleLoc, "angle");
	glEnableVertexAttribArray(angleLoc);
	
	texture.getTextureReference().bind();
	mesh.drawVertices();
	texture.getTextureReference().unbind();
	shader.end();
	ofDisablePointSprites();
	
	// disable vertex attributes
	glDisableVertexAttribArray(pointAttLoc); 
	glDisableVertexAttribArray(angleLoc);
	
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 100, 100, ofColor::black, ofColor::yellow);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'f') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(!hasMouse)
	{
		hasMouse = true;
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		home[i].x = ofRandomWidth();
		home[i].y = ofRandomHeight();
	}
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
