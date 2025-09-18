#include "ofApp.h"
// added to make the pause case insensitive
#include <cctype>
//--------------------------------------------------------------
void ofApp::setup() {
     ofSetFrameRate(60);

    for (int i = 0; i < 3; i++) {
        spawnAsteroid();
    }
    backgroundImage.load("images/asteroid_background.png");

    gameState = TITLE;

    titleScreen.load("images/asteroids_title.png");

    if (!music.load("music/asteroid_song.mp3")) {
        ofLogError() << "Failed to load asteroid_song.mp3!";
    } else if(gameState == PLAYING){
        music.setLoop(true);
        music.play();
    }

    ship.setPosition(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
    ship.setAngle(0);

    thrustSound.load("sounds/thrust.wav");
    fireSound.load("sounds/fire.wav");
    explosionSound.load("sounds/explosion.wav");
    crashSound.load("sounds/crash.wav");

    thrustSound.setLoop(true);  
    fireSound.setMultiPlay(true); 
    explosionSound.setMultiPlay(true);
    crashSound.setMultiPlay(false);

    score = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    // isPaused
    if(isPaused){
        return;
    }

    float dt = ofGetLastFrameTime();

    if(gameState == GAME_OVER) {
        return;
    }

    if(gameState == PLAYING){

        ship.update(dt);
        for (auto &a : asteroids) a.update(dt);
        checkCollisions();

        // Update spawn timer (fixed for windows)
       float currentTime = ofGetElapsedTimef(); // time since app started in seconds
        if (currentTime - lastAsteroidSpawnTime >= asteroidSpawnInterval) {
        spawnAsteroid();                // spawn new asteroid
        lastAsteroidSpawnTime = currentTime; // reset last spawn
    }

        for (int i = bullets.size()-1; i >= 0; i--) {
            bullets[i].update(dt);

            if (!bullets[i].alive) {
                bullets.erase(bullets.begin() + i);
            }
        }

        for (int i = explosions.size() - 1; i >= 0; i--) {
            explosions[i].update(dt);
            if (explosions[i].isDead()) explosions.erase(explosions.begin() + i);
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw() {

    if (gameState == TITLE) {
    if (titleScreen.isAllocated()) {
        titleScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    }

    else if (gameState == PLAYING) {
        //when paused i want the screen to be clear or just a black background
        if(isPaused){
        ofClear(0, 0, 0, 255); 
    } else {

        if (backgroundImage.isAllocated()){
        backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());

    }else{
        ofClear(0, 0, 0, 255); 
    }

      ship.draw();

    // Draw bullets
    ofSetColor(255, 255, 255);
    for (auto &b : bullets) ofDrawCircle(b.position, 3);

    // Draw asteroids
    for (auto &a : asteroids) a.draw();

    //Draw explosion
    for (auto &e : explosions) {
    e.draw();
    }       

    ofSetColor(255);
    ofDrawBitmapString("Press SPACEBAR to shoot", 10, 65);

    //if statement for displaying mute/unmute
    if(isMuted){
        ofDrawBitmapString("Press M to Mute", 10, 80);
    }else{
        ofDrawBitmapString("Press M to Unmute", 10, 80);
    }
    //Draw score
    ofDrawBitmapString("Score:" + ofToString(score), 10, 20);
    }
}

    else if (gameState == GAME_OVER) {
        ofExit();
        
        return;
    }

    // isPaused
    if(isPaused){
        ofSetColor(255);
        ofDrawBitmapString("=== GAME PAUSED ===", ofGetWidth()/2 - 60, ofGetHeight()/2 - 20);
        ofDrawBitmapString("Press P to Resume", ofGetWidth()/2 - 60, ofGetHeight()/2 + 0);
        ofDrawBitmapString("Press R to Restart", ofGetWidth()/2 - 60, ofGetHeight()/2 + 20);
        ofDrawBitmapString("Press E to Exit", ofGetWidth()/2 - 60, ofGetHeight()/2 + 40);
    }

  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(gameState == TITLE){
        if (key == ' '){
            music.play();
            gameState = PLAYING;
        }
    }
    else if(gameState == PLAYING){
    if (key == 'a')  ship.rotateLeft();
    if (key == 'd') ship.rotateRight();
    if (key == 'w' && gameState != GAME_OVER){
        ship.startThrust();
        thrustSound.play();
    }
    if (key == ' ') {
        shoot();
        fireSound.play();
    }
    //new if statement for muting/unmuting
    if(tolower(key) == 'm'){
        isMuted = !isMuted;
        music.setPaused(isMuted);
    }
    //new if statement for pausing , restarting and exiting
    if(gameState == PLAYING && tolower(key) == 'p'){
        isPaused = !isPaused;
        music.setPaused(isPaused);
    }

        if(isPaused){
            if(tolower(key) == 'r'){
                restartGame(); 
            }
            if(tolower(key) == 'e'){
                ofExit(); 
            }
        }
    }
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == 'a' || key == 'd') ship.stopRotating();
    if (key == 'w') {
        ship.stopThrust();
        thrustSound.stop();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
}


//--------------------------------------------------------------
void ofApp::spawnAsteroid(float x, float y, int size) {
    ofVec2f pos;
    if (x < 0 || y < 0) {
        float safeDistance = 100; 
        do {
            pos.set(ofRandomWidth(), ofRandomHeight());
        } while (pos.distance(ship.getPosition()) < safeDistance);
    } else {
        pos.set(x, y);
    }
    asteroids.push_back(Asteroid(pos, size));
}

void ofApp::shoot() {
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastShotTime >= shotCooldown) {
        float angleRad = ofDegToRad(ship.getAngle());
        ofVec2f dir(cos(angleRad), sin(angleRad));
        dir.normalize();

        float bulletSpeed = 400; // pixels per second
        Bullet b(ship.getPosition(), dir * bulletSpeed);

        bullets.push_back(b);
        lastShotTime = currentTime;
    }
}

void ofApp::checkCollisions() {

    // Ship-asteroid collisions
    for (auto &a : asteroids) {
       if (!ship.isInvincible() && ship.getPosition().distance(a.getPosition()) < a.getRadius()) {
        lives--;

        if (lives > 0) {
            crashSound.play();

            ship.setPosition(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
            ship.setVelocity(ofVec2f(0,0));
            ship.setAngle(0);

            bullets.clear();
            
            ship.startInvincibility(invincibleDuration);
        } else {
            gameState = GAME_OVER;
            music.stop();
        }

        return;
    }
    }

     // Bullet–asteroid collisions
    for (int i = bullets.size() - 1; i >= 0; i--) {
        for (int j = asteroids.size() - 1; j >= 0; j--) {
            if (bullets[i].position.distance(asteroids[j].getPosition()) < asteroids[j].getRadius()) {
                

               // Spawn fragments (crumbles)
                int numFragments = 5 + ofRandom(3); // 5–7 fragmented asteroid
                for (int f = 0; f < numFragments; f++) {
                    float angle = ofRandom(TWO_PI);
                    float speed = ofRandom(50, 150); // pixels/sec
                    ofVec2f vel(cos(angle) * speed, sin(angle) * speed);
                    explosions.push_back(Explosion(asteroids[j].getPosition(), vel, asteroids[j].getRadius() * 0.2));
                }
                // break asteroid into smaller pieces
                vector<Asteroid> fragments = asteroids[j].breakApart();

                // remove old asteroid and bullet
                asteroids.erase(asteroids.begin() + j);
                bullets.erase(bullets.begin() + i);

                // add fragments
                asteroids.insert(asteroids.end(), fragments.begin(), fragments.end());

                // increase score
                score += 100;

                //play break sound
                explosionSound.play();

                break; // bullet is gone, move to next bullet
            }
        }
    }
    
}
// new function restartGame()
void ofApp::restartGame(){
asteroids.clear();
bullets.clear();
explosions.clear();

ship.setPosition(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
ship.setVelocity(ofVec2f(0,0));
ship.setAngle(0);

lives = 3;
score = 0;
isPaused = false;

music.setPaused(false);
music.play();

}
