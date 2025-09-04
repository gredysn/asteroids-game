#pragma once
#include "ofMain.h"

class Explosion {
public:
    Explosion(ofVec2f pos, ofVec2f vel, float size);

    void update(float dt);
    void draw();

    bool isDead() const { return dead; }

private:
    ofVec2f position;
    ofVec2f velocity;
    float radius;
    float lifetime = 0.5f; // fragments last half a second
    float age = 0;
    bool dead = false;
};
