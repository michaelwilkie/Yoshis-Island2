#ifndef Entity_H
#define Entity_H

#include "MYSDL_FUNC.h"

struct Circle
{
	int x, y;
	int r;
};
typedef struct VECTOR
{
	float x, y;
	VECTOR(float x = 0, float y = 0)
		: x(x), y(y) {}
	VECTOR operator*(const float e) { return VECTOR(x * e, y * e); }
	VECTOR operator+(const float e) { return VECTOR(x + e, y + e); }
	VECTOR operator-(const float e) { return VECTOR(x - e, y - e); }
	VECTOR operator+(const VECTOR v) { return VECTOR(x + v.x, y + v.y); }
	void operator+=(const VECTOR &v) { x += v.x;	y += v.y; }
	void operator-=(const VECTOR &v) { x -= v.x;	y -= v.y; }
	void operator*=(const VECTOR &v) { x *= v.x;	y *= v.y; }
}VECTOR;
class Particle;

enum Yoshi_Anim
{
	YOSHI_IDLE0 = 0,
	YOSHI_IDLE1,
	YOSHI_IDLE2,
	YOSHI_WALK,
	YOSHI_FALL,
	YOSHI_JUMP
};
class Entity
{
public:
	//The dimensions of the dot
	static const int TOTAL_PARTICLES = 30;
	static const int ENT_WIDTH = 28;
	static const int ENT_HEIGHT = 28;
	static const int TOP = 1;
	static const int SIDE = 3;
	static const int DIR_LEFT = 0;
	static const int DIR_RIGHT = 1;
	SDL_Rect gSpriteClips[6][10];
	// Maximum velocity of the Entity
	const float ENT_VEL = 5.0;

	//Initializes the variables
	Entity(int x, int y);

	Entity();

	~Entity();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Entity and checks collision
	void move(SDL_Rect& wall);

	void stopJumping();
	void jump();
	bool canJump();
	bool jumpflag;
	bool collideflag;
	//Shows the Entity on the screen relative to the camera
	void render(int camX, int camY, Yoshi_Anim e, int frame);

	//Enable/Disable particle effects
	void ShowParticles();
	void HideParticles();

	bool isParticleEnabled();
	bool isMoving();
	bool isFalling();

	//Position accessors
	float getPosX();
	float getPosY();

	VECTOR getVelocity();

	//Gets the collision boxes
	//std::vector<SDL_Rect>& getColliders();

	//Gets collision circle
	Circle& getCollider();

	// Texture of Entity
	LTexture gTexture;
	int gTextureWidth;
	int gTextureHeight;

private:
	//The particles
	Particle* particles[30];

	//Shows the particles
	void renderParticles(int camX, int camY);
	void _moveX(SDL_Rect& wall, VECTOR& prev);
	void _moveY(SDL_Rect& wall, VECTOR& prev);

	int direction;
	int lastdirection;
	float mPosX, mPosY;
	float mVelX, mVelY;
	VECTOR position;
	VECTOR velocity;
	VECTOR gravity;
	bool particleFX;
	bool bJump;
	//Entity's collision boxes
	//std::vector<SDL_Rect> mColliders;
	SDL_Rect last;
	SDL_Rect mCollider;

	//Entity's collision circle
	Circle cCollider;

	//Moves the collision boxes relative to the Entity's offset
	void shiftColliders();

};
#endif