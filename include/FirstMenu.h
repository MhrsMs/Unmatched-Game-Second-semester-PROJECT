#pragma once
#include <raylib.h>
#include <vector>
#include "InputNumber.h"

class FirstMenu
{
public:
	int run_first();
	std::vector <int> run_age();
	std::vector <int> run_legend(int a);
private:
	void load_first();
	void load_age();
	void load_legend();
	void unload_first();
	void unload_age();
	void unload_legend();
	void update();
	void draw_first();
	void draw_age();
	void draw_legend(int a, int b);
	int checkButtons_first();
	int checkbuttons_legend();
private:
	Texture2D back;
	Texture2D button;
	Texture2D unmatched;
	Texture2D age;
	Texture2D legend;
	Texture2D dark;
	Rectangle startrect;
	Rectangle loadrect;
	Rectangle exitrect;
	Rectangle age1rect;
	Rectangle age2rect;
	Rectangle okrect;
	Rectangle legend1rect;
	Rectangle legend2rect;
	Rectangle legend3rect;
	Font font = LoadFont("Assets/font.ttf");
	InputNumber num_age1;
	InputNumber num_age2;
	int activeInput;
};

