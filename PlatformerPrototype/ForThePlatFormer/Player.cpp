#include "stdafx.h"
#include "Player.h"

void Player::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitcher = true;
}

void Player::initVariables()
{

	this->animState = PLAYERANIMATIONSTATE::IDLE;
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texturesheet);

	

	//after sitting up the texture above, this function cuts off from the sheet we have rendered as a texture
	//so basically, you create multiple textures, cut from the sheet, or you change the values of the intrect;
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(this->currentFrame); 
	this->sprite.setScale(2.f, 2.f);
	this->sprite.setPosition(sf::Vector2f(5, 400));
}

void Player::initTexture()
{
	if (! this->texturesheet.loadFromFile("Textures/Idle-Sheet.png")) {
		std::cout << "ERROR::PLAYER.CPP::INITTEXTURE::failed to load the texture" << std::endl;
	}
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
	
}

Player::~Player()
{
}

void Player::updateMovement()
{

	// being idle
	this->animState = PLAYERANIMATIONSTATE::IDLE;

	// left movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->move(-1.f, 0.f);
		this->animState = PLAYERANIMATIONSTATE::MOVING_LEFT;
	}

	//right movement
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->move(1.f, 0.f);
		this->animState = PLAYERANIMATIONSTATE::MOVING_RIGHT;
	}
/*	// up movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->sprite.move(0.f, -3.f);
		this->animState = PLAYERANIMATIONSTATE::JUMPING;
	}

	//down movement
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->sprite.move(0.f, 3.f);
		this->animState = PLAYERANIMATIONSTATE::FALLING;
	}
	*/
}

void Player::initPhysics()
{
	this->velocityMax = 8.f;
	this->acceleration = 1.8f;
	this->drag = 0.85f;
	this->velocityMin = 1.f;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::updateAnimation()
{
	if (this->animState == PLAYERANIMATIONSTATE::IDLE) {


		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->GetAnimSwitch() ) {
			// to change the character animations
				/*
				basically what is happening down there, is that you can change on the current frame values,
				since between each character in the sheet is 68px, and just a reminder, we started from the right of the picture
				which makes the currentframe on its maximum, we just decrease 68 frames every 0.5 seconds using the if condition
				above, that has a timer, and when it reaches to zero, it just goes back to the beginning which is the highest value
				some nice concept

				over here we rendered the idle movement, standing still but changing in animation
				*/
			this->currentFrame.top = 0;
				this->currentFrame.left += 64.f;
				if (this->currentFrame.left >= 256.f) {
					this->currentFrame.left = 0.f;
				}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYERANIMATIONSTATE::MOVING_LEFT || this->GetAnimSwitch()) {

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 80;
			this->currentFrame.left -= 79.f;
			if (this->currentFrame.left <= 0.f) {
				this->currentFrame.left = 560.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}

	}
	else if (this->animState == PLAYERANIMATIONSTATE::MOVING_RIGHT || this->GetAnimSwitch()) {

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 160;
			this->currentFrame.left += 79.f;
			if (this->currentFrame.left >= 560.f) {
				this->currentFrame.left = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
}

void Player::updatePhysics()
{

	//deceleration update

	this->velocity *= this->drag;

	//limit deceleration

	if (abs(this->velocity.x) < this->velocityMin) {
		this->velocity.x = 0.f;
	}
	if (abs(this->velocity.y) < this->velocityMin) {
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{
	// will have the acceleration

	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.y += dir_y * this->acceleration; this one is to control gravity :D


	//it will limit the velocity

	if (std::abs(this->velocity.x) > this->velocityMax) {

		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.0f : 1.f);
	}
}

const bool& Player::GetAnimSwitch()
{
	bool animswitch = this->animationSwitcher;

	if (this->animationSwitcher) {
		this->animationSwitcher = false;
	}

	return animswitch;
}

void Player::resetTimer()
{
	this->animationTimer.restart();
	this->animationSwitcher = true;
}

