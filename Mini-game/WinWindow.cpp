#include "pch.h"
#include "WinWindow.h"

WinWindow::WinWindow() {
	if (!font.loadFromFile("assets/fonts/arial.ttf")) {
		cerr << "An error has occured: font sources/arial.ttf dosn't load" << endl;
	}
}

WinWindow::~WinWindow() {}

String WinWindow::toString(unsigned int a) {
	std::ostringstream oss;
	oss << a;
	return oss.str();
}

bool WinWindow::run(unsigned int steps) {
	window.create(VideoMode(400, 300), "You win", Style::Close);

	text = Text("Congratulate!!!\nYou won for " + toString(steps) + " steps", font, 20);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(Vector2f(400 / 2.0f, 300 / 2.0f));

	while (window.isOpen()) {
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
					break;
				}
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(text);
		window.display();
	}
	return true;
}
