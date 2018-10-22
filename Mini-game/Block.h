#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Block {
private:
	Texture texture;
	Sprite sprite;
	string name;
	int row, col;
protected:
	int width;
public:
	Block();
	~Block();

	void init(int x, int y, int row, int col, int width);
	void setTexture(string name);

	Sprite& getSprite();

	String getName();

	int& getRow();

	int& getCol();
};

