//
//  Ball.cpp
//  turts
//
//  Created by aman on 08/11/2015.
//
//

#include "Ball.hpp"

Ball::Ball(float x, float y) {
    this->pos.set(x,y);
    this->vel.set(0,0);
    this->trail_reset();
    this->damping = 0.99;
}

void Ball::step() {
    this->vel *= damping;
    this->pos += this->vel;
    this->trail.insert(this->trail.begin(), this->pos);
    this->trail.pop_back();
}

void Ball::steer(ofVec3f targetPos, float weight) {
    ofVec3f steer = (targetPos - this->pos) - this->vel;
    this->accel(steer.normalize() * weight);
}

void Ball::cohere(std::vector<Ball> balls, float max_distance, float weight) {
    ofVec3f near_average;
    ofVec3f velo_average;
    float balls_in_neighbourhood = 0.0;
    for( auto ball : balls) {
        if((this->pos.distance(ball.pos) < max_distance) &&
           (&ball != this)) {
            near_average += ball.pos;
            velo_average += ball.vel;
            balls_in_neighbourhood++;
        }
    }
    if (near_average.length() > 1) {
        //    ofSetColor(ofColor::blue);
        //    ofFill();
        near_average /= balls_in_neighbourhood;
        //    ofDrawRectangle(near_average, 10, 10);
        velo_average /= balls_in_neighbourhood;
        this->steer(near_average, weight);
        this->accel(((velo_average) - this->vel) * weight);
    }
}

void Ball::repel(std::vector<Ball> balls, float min_distance, float weight) {
    ofVec2f sum;
    for( auto ball : balls ) {
        if(this->pos.distance(ball.pos) < min_distance) {
            ofVec2f vecToSelf = this->pos - ball.pos;
            float dist = vecToSelf.length();
            vecToSelf = vecToSelf.normalize() * (dist - min_distance) * weight;
            ball.accel(-vecToSelf);
            this->accel(vecToSelf);
            
        }
    }
    sum = sum.normalize();
}

void Ball::repel_touches(std::vector<ofVec3f> touches, float dist_scale, float weight) {
    ofVec2f sum;
    for( auto touch : touches ) {
        ofVec2f touch_pos = ofVec2f(touch.x, touch.y);
        float force = touch.z;
        if(this->pos.distance(touch_pos) < force * dist_scale) {
            ofVec2f vecToSelf = this->pos - touch_pos;
            float dist = vecToSelf.length();
            vecToSelf = vecToSelf.normalize() * (dist - force * dist_scale) * weight;
            this->accel(vecToSelf);
        }
    }
}

void Ball::warp() {
    if(this->pos.x > ofGetWidth()/2 + 10 || this->pos.x < -ofGetWidth()/2 - 10
       || this->pos.y > ofGetHeight()/2 + 10 || this->pos.y < -ofGetWidth()/2 - 10) {
        this->pos *= -1;
        this->pos *= 0.99;
        this->trail_reset();
        
    };
}

void Ball::trail_reset() {
    this->trail.clear();
    for(int i = 0; i < 10; i++) {
        this->trail.insert(this->trail.begin(), this->pos);
    }
}

void Ball::accel(ofVec3f accleration) {
    this->vel = this->vel + accleration;
}
void Ball::setVel(float x, float y) {
    this->vel.set(x, y);
}
void Ball::draw() {
    ofColor blue = ofColor::blue;
    ofColor red = ofColor::red;
    //   ofDrawCircle(this->pos.x, this->pos.y, 3);
    ofPolyline line_trail;
    line_trail.addVertices(trail);
    ofSetColor(blue.lerp(red, this->vel.lengthSquared()/100.0));
    ofFill();
    line_trail.close();
    line_trail.draw();
}