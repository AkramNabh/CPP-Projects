// ForThePlatFormer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Game.h"

int main()
{

	srand(static_cast<unsigned>(time(0)));


	Game game;
	while (game.getWindow().isOpen()) {

		game.update();


		game.render();

	}

}
