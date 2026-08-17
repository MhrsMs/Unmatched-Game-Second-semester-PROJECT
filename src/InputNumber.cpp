#include "InputNumber.h"

InputNumber::InputNumber() : input("")
{
}

void InputNumber::update()
{
	int k = GetCharPressed();
	while (k > 0)
	{
		if (k >= '0' && k <= '9')
		{
			input += static_cast<char>(k);

		}
		k = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE) && !input.empty())
	{
		input.pop_back();
	}
}

void InputNumber::draw(Rectangle r, bool active)
{
	Color border = active ? RED: BLACK;
	DrawRectangleLines(r.x,r.y,r.width,r.height, border);
	DrawTextEx(font, input.c_str(), { r.x+10,r.y+10 }, 40, 2,RED);
}

bool InputNumber::isMouseOver(Rectangle r) const
{
	Vector2 mouse = GetMousePosition();
	return CheckCollisionPointRec(mouse, { static_cast<float>(r.x),static_cast<float>(r.y) ,static_cast<float>(r.width) ,static_cast<float>(r.height) });
}

int InputNumber::getNumber() const
{
	if (input.empty())
	{
		return -1;
	}
	return std::stoi(input);
}

bool InputNumber::isEmpty() const
{
	return input.empty();
}

void InputNumber::reset()
{
	input.clear();
}
