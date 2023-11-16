#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class GameObjects
{
	struct GameObject
	{
		sf::RectangleShape gameObject;
		std::string name;
		bool isDynamic;

		GameObject(sf::RectangleShape, std::string, bool);
	};

	std::vector <GameObject> gameObjects;

	public:
		sf::RectangleShape& operator [] (std::string);
		sf::RectangleShape& operator[] (int);
		bool IfDynamic(std::string);
		bool IfDynamic(int);
		std::string GetName(int);
		int Size() { return this->gameObjects.size(); };
		void Insert(sf::RectangleShape, std::string, bool);
		void Delete(std::string);

};



