#include "GameObjects.h"

GameObjects::GameObject::GameObject(sf::RectangleShape gameObject, std::string name, bool isDynamic)
{
	this->gameObject = gameObject;
	this->name = name;
	this->isDynamic = isDynamic;
}

sf::RectangleShape& GameObjects::operator [] (std::string name)
{
	int i = 0;
	bool found = false;

	for (i = 0; i < this->gameObjects.size(); i++)
	{
		if (gameObjects[i].name == name)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		throw std::invalid_argument("gameObject not found!");
		}


	return this->gameObjects[i].gameObject;
}

sf::RectangleShape& GameObjects::operator[] (int index)
{
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		if (i == index)
			break;
	}

	return this->gameObjects[index].gameObject;
}

std::string GameObjects::GetName(int i)
{
	return this->gameObjects[i].name;
}

bool GameObjects::IfDynamic(std::string name)
{
	int i = 0;
	bool found = false;
	for (i = 0; i < this->gameObjects.size(); i++)
	{
		if (gameObjects[i].name == name)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		throw std::invalid_argument("gameObject not found!");
	}


	return this->gameObjects[i].isDynamic;
}

bool GameObjects::IfDynamic(int index)
{
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		if (i == index)
		{
			break;
		}
	}

	return this->gameObjects[index].isDynamic;
}

void GameObjects::Insert(sf::RectangleShape gameObject, std::string name, bool isDynamic)
{
	this->gameObjects.push_back(GameObjects::GameObject(gameObject, name, isDynamic));
}

void GameObjects::Delete(std::string name)
{
	int i = 0;
	bool found = false;

	for (i = 0; i < this->gameObjects.size(); i++)
	{
		if (this->gameObjects[i].name == name)
		{
			found = true;

			this->gameObjects.erase(this->gameObjects.begin() + i);

			break;
		}
	}

	if (!found)
	{
		throw std::invalid_argument("gameObject not found!");
	}

}