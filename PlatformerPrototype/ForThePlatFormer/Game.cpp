#include "stdafx.h"
#include "Game.h"
void Game::initVariables()
{
}
void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Platformer", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}
void Game::initPlayer()
{
	this->player = new Player();
}
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	//delete this->window;
	delete this->player;
}

void Game::update()
{
	//polling the event

	while (this->window.pollEvent(this->event)) {

		if (this->event.type == sf::Event::Closed) {

			this->window.close();
		}
		else if (event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape) {

			this->window.close();
		}

		if (event.type == sf::Event::KeyReleased &&
			(this->event.key.code == sf::Keyboard::A ||
				this->event.key.code == sf::Keyboard::D ||
				this->event.key.code == sf::Keyboard::W ||
				this->event.key.code == sf::Keyboard::S)) {

			this->player->resetTimer();
		}


		this->updatePlayer();
	}
}
void Game::render()
{
	this->window.clear();

	//this is where you draw with this->window.draw();
	this->renderPlayer();

	this->window.display();
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
