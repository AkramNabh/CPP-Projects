#include "stdafx.h"
#include "Player.h"
#pragma once
class Game
{

private:
	// variables

	sf::RenderWindow window;
	sf::Event event;

	Player* player;


	// some initializers

	void initVariables();
	void initWindow();
	void initPlayer();
public:
	Game();
	~Game();


	//functions
	void update();
	void render();
	void updatePlayer();
	void renderPlayer();
	const sf::RenderWindow& getWindow() const;
};

