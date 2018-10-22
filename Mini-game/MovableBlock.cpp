#include "pch.h"
#include "MovableBlock.h"
#include "Block.h"
#include <iostream>
#include "Engine.h"

MovableBlock::MovableBlock() {
	isMove = false;
}

MovableBlock::~MovableBlock() {}

bool& MovableBlock::getIsMove() {
	return isMove;
}

bool MovableBlock::check(vector<vector<int>> &gameField, queue<Vector2i> &cellsAfterClick) {
	if (gameField[cellsAfterClick.back().y][cellsAfterClick.back().x] == -1) {
		Vector2i temp(cellsAfterClick.back() - cellsAfterClick.front());
		if ((abs(temp.x) == 1 && temp.y == 0) || (abs(temp.y) == 1 && temp.x == 0)) {
			return true;
		}
	}
	return false;
}

void MovableBlock::update(Vector2i coords, vector<vector<int>> &gameField,
	queue<Vector2i> &cellsAfterClick, unsigned int &steps) {
	if (isMove) {
		Vector2i cell(Engine::getCell(coords, this->width));
		if (check(gameField, cellsAfterClick)) {
			steps++;
			this->getRow() = cell.y;
			this->getCol() = cell.x;
			Vector2f origin = this->getSprite().getOrigin();
			this->getSprite().setPosition((cell.x + 1) * this->width + origin.x,
				(cell.y + 1) * this->width + origin.y);
			gameField[cellsAfterClick.front().y][cellsAfterClick.front().x] = -1;
			if (this->getName() == "yellow") {
				gameField[cell.y][cell.x] = 0;
			} else if (this->getName() == "orange") {
				gameField[cell.y][cell.x] = 1;
			} else if (this->getName() == "red") {
				gameField[cell.y][cell.x] = 2;
			}
			while (cellsAfterClick.size() > 1) {
				cellsAfterClick.pop();
			}
		}
	}
}