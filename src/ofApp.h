#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Explosion.h"
#include <vector>

class ofApp : public ofBaseApp {

enum GameState {
    TITLE,
    PLAYING,
    GAME_OVER
};

public:
	GameState gameState;
	ofTrueTypeFont titleFont;


    void setup() override;
    void update() override;
    void draw() override;
	

    void keyPressed(int key) override;
    void keyReleased(int key) override;
	void mouseMoved(int x, int y) override;
	void mousePressed(int x, int y, int button) override;

private:
    Ship ship;
    vector<Asteroid> asteroids;
	vector<Bullet> bullets;

    int score;
	//new variable for pause state phase 2
	bool isPaused = false;
	//new variable for Muting 
	bool isMuted = false;
	float invincibleDuration = 2.0f;
	float lastAsteroidSpawnTime = 0.0f;
	float asteroidSpawnInterval = 5.0f; // spawn a new asteroid every 5 seconds
    void spawnAsteroid(float x = -1, float y = -1, int size = 3);
    void checkCollisions();
	void shoot();
	//new function for restarting the game
	void restartGame();
	float lastShotTime = 0.0f;      // last time a bullet was fired
    float shotCooldown = 0.1f;      // minimum seconds between shots
	vector<Explosion> explosions;
	int lives = 3;
	//int lives = 10;
	ofImage backgroundImage;
	ofImage titleScreen;
	ofSoundPlayer music;
	ofSoundPlayer thrustSound;
	ofSoundPlayer fireSound;
	ofSoundPlayer explosionSound;
	ofSoundPlayer crashSound;
};
