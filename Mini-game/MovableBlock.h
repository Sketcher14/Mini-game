#pragma once

#include "Block.h"
#include <queue>

using namespace sf;

class MovableBlock : public Block {
private:
	bool isMove;
public:
	MovableBlock();
	~MovableBlock();

	void update(Vector2i coords, vector<vector<int>> &gameField, queue<Vector2i> &cellsAfterClick, unsigned int &steps);
	bool check(vector<vector<int>> &gameField, queue<Vector2i> &cellsAfterClick);

	bool& getIsMove();
};

