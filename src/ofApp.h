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
	int highScore; //variable for the high score
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
	void restartGame(); //new function for restarting the game
	float lastShotTime = 0.0f;      // last time a bullet was fired
    float shotCooldown = 0.1f;      // minimum seconds between shots
	vector<Explosion> explosions;
	int lives = 3;
	int maxLives = 5;
	int lifeAward = 1500; // award for a life when scored
	//adding the shipSprite
	ofImage shipSprite;
	ofImage backgroundImage;
	ofImage titleScreen;
	ofImage gameOverScreen;
	ofSoundPlayer music;
	ofSoundPlayer thrustSound;
	ofSoundPlayer fireSound;
	ofSoundPlayer explosionSound;
	ofSoundPlayer crashSound;
};
