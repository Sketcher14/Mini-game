#include "pch.h"
#include "Engine.h"

using namespace std;

Engine::Engine() {
	countUB = 6;
	countMB = 15;
	countCB = 3;
	steps = 0;
	gameField.resize(5, vector<int>(5, -1));

	screenHeight = VideoMode::getDesktopMode().height;
	sizeBlock = screenHeight / 7;
	window.create(VideoMode(sizeBlock * 7, sizeBlock * 7), "Mini-game", Style::Close);

	if (!backgroundTexture.loadFromFile("assets/images/newBackground.jpg")) {
		cerr << "An error has occured: background dosn't load" << endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale((float)window.getSize().x / backgroundTexture.getSize().x,
		(float)window.getSize().y / backgroundTexture.getSize().y);


	unmovableBlocks = new Block[countUB];
	movableBlocks = new MovableBlock[countMB];
	colorsBlocks = new Block[countCB];

	initializationBlocks();
}

Engine::~Engine() {
	delete[] unmovableBlocks;
	delete[] movableBlocks;
	delete[] colorsBlocks;
}

void Engine::initializationBlocks() {
	vector<int> sequence = generationSequence(countMB, 3, 3);
	int row = 0, col = 0;
	for (int i = 0; i < countMB; ++i) {
		switch (sequence[i]) {
		case 0:
		{
			movableBlocks[i].setTexture("yellow");
			movableBlocks[i].init((col + 1) * sizeBlock, (row + 1) * sizeBlock, row, col, sizeBlock);
			gameField[row][col] = 0;
			break;
		}
		case 1:
		{
			movableBlocks[i].setTexture("orange");
			movableBlocks[i].init((col + 1) * sizeBlock, (row + 1) * sizeBlock, row, col, sizeBlock);
			gameField[row][col] = 1;
			break;
		}
		case 2:
		{
			movableBlocks[i].setTexture("red");
			movableBlocks[i].init((col + 1) * sizeBlock, (row + 1) * sizeBlock, row, col, sizeBlock);
			gameField[row][col] = 2;
			break;
		}
		default:
			break;
		}

		col = ((i + 1) / 5) * 2;
		row++;
		if (row > 4) {
			row = 0;
		}
	}
	row = 0;
	col = 1;
	for (int i = 0; i < countUB; ++i) {
		unmovableBlocks[i].setTexture("greenWithBlueBlock");
		unmovableBlocks[i].init((col + 1) * sizeBlock, (row + 1) * sizeBlock, row, col, sizeBlock);
		gameField[row][col] = 3;
		col = ((i + 1) / 3) * 2 + 1;
		row += 2;
		if (row > 4) {
			row = 0;
		}
	}
	vector<int> sequence2{ 0, 1, 2 };
	random_shuffle(sequence2.begin(), sequence2.end());
	for (int i = 0; i < countCB; ++i) {
		switch (sequence2[i]) {
		case 0:
		{
			colorsBlocks[i].setTexture("yellowBlock");
			colorsBlocks[i].init((i * 2 + 1) * sizeBlock, 0, -1, -1, sizeBlock);
			break;
		}
		case 1:
		{
			colorsBlocks[i].setTexture("orangeBlock");
			colorsBlocks[i].init((i * 2 + 1)  * sizeBlock, 0, -1, -1, sizeBlock);
			break;
		}
		case 2:
		{
			colorsBlocks[i].setTexture("redBlock");
			colorsBlocks[i].init((i * 2 + 1)  * sizeBlock, 0, -1, -1, sizeBlock);
			break;
		}
		default:
			break;
		}
	}
}

vector<int> Engine::generationSequence(int n, int m, int k) {
	vector<int> result(0), countColors(3, 0);
	srand(time(0));
	int streak = 1;
	for (size_t i = 0; i < n; ++i) {
		int x = rand() % m;
		if (i > 1 && result[result.size() - 1] == x) {
			streak++;
		} else {
			streak = 1;
		}
		if (streak == k) {
			while (x == result[result.size() - 1]) {
				x = rand() % 3;
			}
		}
		if (++countColors[x] > 5) {
			i--;
			continue;
		}
		result.push_back(x);
	}
	return result;
}

Vector2i Engine::getCell(Vector2i mousePos, int size) {
	mousePos -= Vector2i(size, size);
	Vector2i cell(0, 0);
	while (mousePos.x > size - 1) {
		cell.x++;
		mousePos.x -= size;
	}
	while (mousePos.y > size - 1) {
		cell.y++;
		mousePos.y -= size;
	}
	return cell;
}

void Engine::start() {

	int targetSprite = -1;

	while (window.isOpen()) {

		Vector2i mousePos = Mouse::getPosition(window);
		mousePos = Vector2i(mousePos.x % (sizeBlock * 6), mousePos.y % (sizeBlock * 6));

		if (!cellsAfterClick.empty()) {
			Vector2i tempCell(getCell(mousePos, sizeBlock));
			if (cellsAfterClick.back() != tempCell)
				cellsAfterClick.push(tempCell);
		}

		Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::KeyPressed:
			{
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				break;
			}
			case Event::MouseButtonPressed:
			{
				if (event.key.code == Mouse::Left) {
					for (int i = 0; i < countMB; ++i) {
						if (movableBlocks[i].getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							targetSprite = i;
							cellsAfterClick.push(Vector2i(movableBlocks[i].getCol(), movableBlocks[i].getRow()));
							movableBlocks[i].getIsMove() = true;
						}
					}
				}
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.key.code == Mouse::Left) {
					movableBlocks[targetSprite].getIsMove() = false;
					while (!cellsAfterClick.empty()) {
						cellsAfterClick.pop();
					}
				}
				break;
			}
			default:
				break;
			}
		}

		if (winCondition()) {
			if (winWindow.run(steps)) {
				break;
			}
		}
		update(mousePos);
		draw();
	}
}

void Engine::update(Vector2i coords) {
	for (size_t i = 0; i < countMB; ++i) {
		movableBlocks[i].update(coords, gameField, cellsAfterClick, steps);
	}
}

bool Engine::winCondition() {
	vector<bool> ans(5, true);
	for (int i = 0; i < countCB; ++i) {
		int curColor = -1;
		if (colorsBlocks[i].getName() == "yellowBlock") {
			curColor = 0;
		} else if (colorsBlocks[i].getName() == "orangeBlock") {
			curColor = 1;
		} else if (colorsBlocks[i].getName() == "redBlock") {
			curColor = 2;
		}
		for (int j = 0; j < 5; ++j) {
			if (gameField[j][i * 2] != curColor) {
				ans[i * 2] = false;
			}
		}
	}
	return ans[0] && ans[2] && ans[4];
}

void Engine::draw() {
	window.clear();
	window.draw(backgroundSprite);
	for (size_t i = 0; i < countMB; ++i) {
		window.draw(movableBlocks[i].getSprite());
	}
	for (size_t i = 0; i < countUB; ++i) {
		window.draw(unmovableBlocks[i].getSprite());
	}
	for (size_t i = 0; i < countCB; ++i) {

		window.draw(colorsBlocks[i].getSprite());
	}
	window.display();
}