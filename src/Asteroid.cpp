#include "Asteroid.h"

Asteroid::Asteroid() {
    position.set(ofRandomWidth(), ofRandomHeight());
    velocity.set(ofRandom(-2, 2), ofRandom(-2, 2));
    size = 3;
    radius = size * 20;

    //new rotation
    angle = ofRandom(0, 360);
    //different speeds for each asteroid
    if(size == 3) angularSpeed = ofRandom(-360, 360);
    if(size == 2) angularSpeed = ofRandom(-150, 150);
    if(size == 1) angularSpeed = ofRandom(-180, 180);

}

Asteroid::Asteroid(ofVec2f pos, int s) {
    position = pos;
    velocity.set(ofRandom(-2, 2), ofRandom(-2, 2));
    size = s;
    radius = size * 20;
    //random rotation for each asteroid
    angle = ofRandom(0, 360);
    if(size == 3) angularSpeed = ofRandom(-90, 90);
    if(size == 2) angularSpeed = ofRandom(-150, 150);
    if(size == 1) angularSpeed = ofRandom(-180, 180);

    int points = 8 + ofRandom(3); // 8-10 points
    for (int i = 0; i < points; i++) {
        float angle = ofMap(i, 0, points, 0, TWO_PI);
        float r = radius * ofRandom(0.7, 1.3); // jagged
        shape.push_back(ofVec2f(cos(angle) * r, sin(angle) * r));
    }
    float maxSpeed = 5; 
    float minSpeed = 1;
    float angle = ofRandom(TWO_PI);
    float speed = ofRandom(minSpeed, maxSpeed);
    velocity = ofVec2f(cos(angle), sin(angle)) * speed;
}

void Asteroid::update(float dt) {

    //Required for windows to run at 60fps DO NOT CHANGE
    dt = ofGetLastFrameTime();
    if (dt <= 0) dt = 0.016f;

    position += velocity;

    //updating rotating angle
    angle += angularSpeed * dt;
     if(angle > 360) angle -= 360;
     if(angle < 0) angle += 360;
    
    // Wrap screen
    if (position.x < 0) position.x += ofGetWidth();
    if (position.x > ofGetWidth()) position.x -= ofGetWidth();
    if (position.y < 0) position.y += ofGetHeight();
    if (position.y > ofGetHeight()) position.y -= ofGetHeight();
}

void Asteroid::draw() const {
    ofPushMatrix();
    ofTranslate(position);
   ofRotateDeg(angle);//applying the rotation

        ofSetColor(250);
        ofBeginShape();
        for (auto &v : shape) {
            ofVertex(v.x, v.y);
        }
        ofEndShape(true);

    ofPopMatrix();
}

ofVec2f Asteroid::getPosition() const { return position; }
float Asteroid::getRadius() const { return radius; }
int Asteroid::getSize() const { return size; }

vector<Asteroid> Asteroid::breakApart() {
    vector<Asteroid> fragments;

    if (size > 1) { // only split if not the smallest
        for (int i = 0; i < 2; i++) {
            ofVec2f newVel = velocity.getRotated(ofRandom(-45, 45));
            newVel *= 1.2; // slightly faster
            Asteroid child(position, size - 1);
            child.velocity = newVel;
            fragments.push_back(child);
        }
    }
    return fragments;
}

