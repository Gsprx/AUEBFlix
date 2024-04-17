#pragma once
#include "hoverable.h"
#include <vector>
#include "movielist.h"

class HoverMenu : public Hoverable {
	unsigned int expanded_width = 0;
	bool expanded = false;
	bool play_expand_sound = false;
	bool play_shrink_sound = false;
	std::vector<Widget*> filters;
	MovieList* movielist;


public:
	bool getExpandedStatus();
	void setMovieList(MovieList* ml);
	void draw() override;
	void update() override;
	void setExpandedWidth(unsigned int w);
	void drawText();
	void init();

	HoverMenu();
	~HoverMenu();
};