#pragma once
#include <raylib.h>
#include <string>
class InputNumber
{
private:
	std::string input;
	Font font = LoadFont("Assets/font.ttf");
public:
	InputNumber();
	void update();
	void draw(Rectangle r, bool active);
	bool isMouseOver(Rectangle r) const;
	int getNumber() const;
	bool isEmpty() const;
	void reset();

};

