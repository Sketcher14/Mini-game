#include "pch.h"
#include "Block.h"
#include "Engine.h"

Block::Block() {}

void Block::init(int x, int y, int row, int col, int width) {
	this->width = width;
	sprite.setScale((float)this->width / this->texture.getSize().x,
		(float)this->width / this->texture.getSize().y);
	sprite.setPosition(x, y);
	this->row = row;
	this->col = col;
}

void Block::setTexture(string name) {
	if (!texture.loadFromFile("assets/images/" + name + ".jpg")) {
		cerr << "An error has occured: texture " << name << ".jpg doesn't load" << endl;
	}
	sprite.setTexture(this->texture);
	this->name = name;
}

Block::~Block() {}

Sprite& Block::getSprite() {
	return sprite;
}

String Block::getName() {
	return name;
}

int& Block::getRow() {
	return row;
}

int& Block::getCol() {
	return col;
}

