#pragma once
#include "movielist.h"
#include "button.h"
#include "widget.h"
#include "hovermenu.h"

class ScreenShotList : public Widget {
	MovieList* ml = nullptr;
	HoverMenu* hm = nullptr; //used to check for expanded status 
	Movie* current_movie = nullptr;
	Button* shots_left;
	Button* shots_right;
	int index = 0;

public:
	void addMovieList(MovieList* ml);
	void addHoverMenu(HoverMenu* hm);
	void scroll_left();
	void scroll_right();
	void draw() override;
	void update() override;
	void init();

	ScreenShotList();
	~ScreenShotList();

};
