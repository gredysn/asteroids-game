#pragma once
#include "ofMain.h"

class Asteroid {
public:
    Asteroid();
    Asteroid(ofVec2f pos, int size); // spawn at position with size

    void update(float dt);
    void draw() const;

    ofVec2f getPosition() const;
    float getRadius() const;
    int getSize() const;
    vector<Asteroid> breakApart(); 
    
private:
    ofVec2f position;
    ofVec2f velocity;
    float radius;
    int size; // 3 = large, 2 = medium, 1 = small
    vector<ofVec2f> shape;
    
    //new float for the rotation
    float angle;
    float angularSpeed;
};
