#pragma once
#include <vector>
#include "button.h"
#include "movielist.h"

class FilmBrowser {
	std::vector<Widget *> widgets;
	MovieList* movielist;

public:
	void update();
	void draw();
	void init();

	FilmBrowser();
	~FilmBrowser();

};