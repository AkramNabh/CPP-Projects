#include "stdafx.h"
#pragma once

enum PLAYERANIMATIONSTATE {
	IDLE = 0,
	MOVING_LEFT ,MOVING_RIGHT, JUMPING, FALLING
};
class Player
{

private:

	sf::Sprite sprite;
	sf::Texture texturesheet;
	
	// animation
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	void initAnimation();
	


	//physics

	sf::Vector2f velocity;
	float acceleration;
	float velocityMax;
	float velocityMin;
	float drag;


	//movement



	//core

	void initVariables();
	void initSprite();
	void initTexture();
	void initPhysics();

public:

	Player();
	~Player();


	//accessor
	bool animationSwitcher;
	const bool& GetAnimSwitch();


	void resetTimer();
	void updateMovement();
	void render(sf::RenderTarget& target);
	void update();
	void updateAnimation();
	void updatePhysics();
	void move(const float dir_x, const float dir_y);
};

