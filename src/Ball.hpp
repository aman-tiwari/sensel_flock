//
//  Ball.hpp
//  turts
//
//  Created by aman on 08/11/2015.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "ofMain.h"

class Ball {
public:
    Ball(float, float);
    
    void setVel(float, float);
    
    void steer(ofVec3f, float);
    void repel(std::vector<Ball>, float, float);
    void cohere(std::vector<Ball>, float, float);
    void accel(ofVec3f);
    
    void repel_touches(std::vector<ofVec3f> touches, float dist_scale, float weight);
    
    void draw();
    void step();
    void warp();
    
    float damping;
    
    ofVec2f vel;
    ofVec2f pos;
    
    std::vector<ofPoint> trail;
    void trail_reset();
    
};
#endif /* Ball_hpp */
