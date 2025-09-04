#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(ofVec2f pos, ofVec2f vel) {
    position = pos;
    velocity = vel;
}

void Bullet::update(float dt) {

     //Required for windows to run at 60fps DO NOT CHANGE or bullets won't shoot
    dt = ofGetLastFrameTime();
    if (dt <= 0) dt = 0.016f;

        position += velocity * dt;
        age += dt;
        
    if (age >= lifetime) alive = false;

    // wrap around screen (Asteroids style)
    if (position.x < 0) position.x += ofGetWidth();
    if (position.x > ofGetWidth()) position.x -= ofGetWidth();
    if (position.y < 0) position.y += ofGetHeight();
    if (position.y > ofGetHeight()) position.y -= ofGetHeight();
}

void Bullet::draw() {
    ofSetColor(255);
    ofDrawCircle(position, 2);
}
