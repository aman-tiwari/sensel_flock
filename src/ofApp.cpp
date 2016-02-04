#include "ofApp.h"
#include <vector>

/* Flocking Simulation w/ Sensel Interation */


std::vector<Ball> balls;
std::vector<ofVec3f> touches;
bool AccelToMouse (false);
int whichKey;
int nBalls = 180;
//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofSetFrameRate(60);
    ofFill();
    ofSetColor(ofColor::black);
    
    for( int i = 0; i < nBalls; ++i ) {
        
        Ball temp_ball(ofRandom(-ofGetWindowWidth()/2, ofGetWindowWidth()/2),
                       ofRandom(-ofGetWindowHeight()/2, ofGetWindowHeight()/2));
        
        balls.push_back(temp_ball);
    }
    
    sensel.setup();
};


//--------------------------------------------------------------
void ofApp::update(){
    sensel.update();
    touches.clear();
    
    for(auto contact : sensel.senselContacts) {
        touches.push_back(ofVec3f(contact.position.x * ofGetWidth() - ofGetWidth()/2,
                                  -contact.position.y * ofGetHeight() + ofGetHeight()/2,
                                  contact.force));
    }
};

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    ofBackground(ofColor::white);
    
    for(auto contact : sensel.senselContacts) {
        
        ofPushMatrix();
        
        ofTranslate(contact.position.x * ofGetWidth() - ofGetWidth()/2,
                    -contact.position.y * ofGetHeight() + ofGetHeight()/2);
        ofRotateZ(contact.orientation);
        
        ofSetColor(ofColor::black);
        
        ofDrawEllipse(0, 0, contact.minorAxis * 3 , contact.majorAxis * 3);
        
        ofPopMatrix();
        
    }
    
    drawMono();
    
    cam.end();

};

void ofApp::drawMono() {
    
    
    ofVec3f mouseVec (mouseX, mouseY, 0);
    

    for( auto& ball : balls) {
        int r = rand() % 3; //updates 1/3rd of the agents per frame
        if(r == 0) {
            ball.repel_touches(touches, 500, -0.4);
            ball.cohere(balls, 100, 0.004);
            ball.repel(balls, 20, 0.08);
            if (AccelToMouse) {
                ball.steer(mouseVec, 0.08);
            }
        }
    }
    for( auto& ball : balls) {
        ball.step();
        ball.warp();
    }
    
    for( auto& ball : balls) {
        ball.draw();
    }
        
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    whichKey = key;
    if(key == ' ' || key == 219) {
        ++nBalls;
        Ball temp_ball(ofRandom(-100, 100),
                       ofRandom(-100, 100));
        balls.push_back(temp_ball);
    } else if (key == '-' || key == 221) {
        --nBalls;
        balls.pop_back();
    } else {
        for( auto& ball : balls ) {
            ball.vel.set(0,0);
            ball.pos.set(ofRandom(-ofGetWindowWidth()/2, ofGetWindowWidth()/2),ofRandom(-ofGetWindowHeight()/2, ofGetWindowHeight()/2));
        }
    }
}

void ofApp::exit() {
    sensel.close();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}

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
