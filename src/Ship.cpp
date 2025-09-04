#include "Ship.h"

Ship::Ship() {
    position.set(ofGetWidth()/2, ofGetHeight()/2);
    velocity.set(0, 0);
    angle = 0;
    rotationSpeed = 180; 
    turnDirection = 0;
    isThrusting = false;
    thrust = 450;   //thrusting power at decent speed
    friction = 0.98; //important so ship won't come at a full stop in space
    radius = 10;
}

//--------------------------------------------------------------
void Ship::update(float dt) {

    //Required for windows to run at 60fps DO NOT CHANGE or ship will not run
    dt = ofGetLastFrameTime();
    if (dt <= 0) dt = 0.016f;

    // Rotate ship
    angle += turnDirection * rotationSpeed * dt;

    // Apply thrust
    if (isThrusting) {
        ofVec2f forward(cos(ofDegToRad(angle)), sin(ofDegToRad(angle)));
        velocity += forward * thrust * dt;
    }

 if (invincible) {
    invincibleTimer -= dt;  // instead of ofGetLastFrameTime()
    if (invincibleTimer <= 0) {
        invincible = false;
    }
}

    // Apply friction
    velocity *= friction; 

    // Move ship
    position += velocity * dt;

    // Wrap around screen (So ship won't disappear or crash)
    if (position.x < 0) position.x += ofGetWidth();
    if (position.x > ofGetWidth()) position.x -= ofGetWidth();
    if (position.y < 0) position.y += ofGetHeight();
    if (position.y > ofGetHeight()) position.y -= ofGetHeight();
}


//--------------------------------------------------------------
void Ship::draw() {
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(angle);
    ofRotateDeg(90);
    
   if (invincible) {
        int blink = int(invincibleTimer * 10) % 2; // blink based on remaining invincibility
        if (blink == 0) {
            ofPopMatrix();
            return; 
        }
    }
        ofSetColor(255);
        ofDrawTriangle(0, -10, -7, 10, 7, 10);

    ofPopMatrix();
}

//--------------------------------------------------------------
void Ship::reset() {
    position.set(ofGetWidth() / 2, ofGetHeight() / 2);
    velocity.set(0, 0);
    angle = -90;   
    isThrusting = false;
    invincible = true;
    invincibleTimer = 3.0f;
}


//--------------------------------------------------------------
void Ship::rotateLeft()  { turnDirection = -1; }
void Ship::rotateRight() { turnDirection = 1; }
void Ship::stopRotating() { turnDirection = 0; }

void Ship::startThrust() { isThrusting = true; }
void Ship::stopThrust()  { isThrusting = false; }

void Ship::setPosition(const ofVec2f& pos) {
    position = pos;
}

void Ship::setVelocity(const ofVec2f& vel) {
    velocity = vel;
}

void Ship::setAngle(float a) {
    angle = a;
}

ofVec2f Ship::getPosition() const { return position; }
float Ship::getRadius() const { return radius; }
float Ship::getAngle() const { return angle; }
