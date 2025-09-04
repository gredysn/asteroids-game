#pragma once
#include "ofMain.h"

class Bullet {
public:
    Bullet();
    Bullet(ofVec2f pos, ofVec2f vel);

    void update(float dt);
    void draw();

    ofVec2f position;
    ofVec2f velocity;
    float lifetime = 1.5f;     // seconds bullet lasts
    float age = 0.0f;          // how long the bullet has existed
    bool alive = true;  // can be used to remove bullet if off screen
};
