#include "Explosion.h"

Explosion::Explosion(ofVec2f pos, ofVec2f vel, float s) {
    position = pos;
    velocity = vel;
    radius = s;
}

void Explosion::update(float dt) {

    //Required for windows to run at 60fps DO NOT CHANGE
    dt = ofGetLastFrameTime();
    if (dt <= 0) dt = 0.016f;

    position += velocity * dt;
    age += dt;
    if (age >= lifetime) dead = true;
    velocity *= 0.95; // slow down gradually
}

void Explosion::draw() {
   ofSetColor(180, 180, 180, ofMap(age, 0, lifetime, 255, 0));
    ofDrawCircle(position, radius);
}
