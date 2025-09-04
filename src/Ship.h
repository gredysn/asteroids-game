#pragma once
#include "ofMain.h"

class Ship {
public:
    Ship();

    void update(float dt);
    void draw();

    void rotateLeft();
    void rotateRight();
    void stopRotating();

    void startThrust();
    void stopThrust();

    void setPosition(const ofVec2f& pos);
    void setVelocity(const ofVec2f& vel);
    void setAngle(float a);

    ofVec2f getPosition() const;
    float getRadius() const;
    float getAngle() const;
    void reset();

    void startInvincibility(float duration) {
    invincible = true;
    invincibleTimer = duration;
    }

    bool isInvincible() const {
        return invincible;
    }

private:
    ofVec2f position;
    ofVec2f velocity;
    float angle = 0;          // degrees
    float rotationSpeed;  // degrees per second
    int turnDirection;    // -1 = left, 1 = right, 0 = none
    bool isThrusting;
    float invincibleTimer = 0.0f; 
    bool invincible = false;

    float thrust;   // pixels per second²
    float friction; // multiplier < 1
    float radius;   // for collisions
    
};
