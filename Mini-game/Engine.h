#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <queue>
#include <algorithm>
#include "MovableBlock.h"
#include "Block.h"
#include "WinWindow.h"

using namespace sf;
using namespace std;

class Engine {
private:
	RenderWindow window;
	Sprite backgroundSprite;
	Texture backgroundTexture;

	WinWindow winWindow;

	int countUB, countMB, countCB, sizeBlock;
	unsigned int screenHeight, steps;
	Block *colorsBlocks;
	Block *unmovableBlocks;
	MovableBlock *movableBlocks;
	vector<vector<int>> gameField;
	queue<Vector2i> cellsAfterClick;

	void initializationBlocks();

	vector<int> generationSequence(int n, int m, int k);

	void draw();

	void update(Vector2i coords);

	bool winCondition();
public:
	Engine();
	~Engine();

	static Vector2i getCell(Vector2i mousePos, int size);

	void start();
};

