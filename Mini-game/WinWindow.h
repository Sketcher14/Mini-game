#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class WinWindow {
private:
	RenderWindow window;
	Font font;
	Text text;

	String toString(unsigned int a);

public:

	bool run(unsigned int steps);
	WinWindow();
	~WinWindow();
};

