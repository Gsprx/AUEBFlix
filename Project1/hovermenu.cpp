#include "hovermenu.h"
#include "config.h"
#include "graphics.h"
#include "checkbox.h"
#include "movielist.h"
#include "slider.h"
#include "button.h"

void HoverMenu::setExpandedWidth(unsigned int w)
{
	expanded_width = w;
}

HoverMenu::HoverMenu()
{
}

HoverMenu::~HoverMenu()
{
	for (auto filter : filters) {
		delete filter;
	}
	filters.clear();
}

bool HoverMenu::getExpandedStatus()
{
	return expanded;
}

void HoverMenu::setMovieList(MovieList* ml)
{
	movielist = ml;
}

void HoverMenu::draw()
{						
											// determine draw orientation
	if (orientation != NULL) {
		graphics::setOrientation(orientation);
	}

	graphics::setFont((std::string)ASSET_PATH + "DejaVuSansMono-Bold.ttf"); //load selected font
	if (expanded == false) {
		graphics::Brush br;					// shrink-normal draw when not hovered upon
		br.outline_opacity = 0.4f;
		br.fill_color[0] = 28.f / 255;
		br.fill_color[1] = 28.f / 255;
		br.fill_color[2] = 28.f / 255;
		br.fill_opacity = 0.25f;
		graphics::drawRect(pos_x, pos_y, width, height, br);
		play_expand_sound = true;
		drawText();
		if (play_shrink_sound) {
			graphics::playSound((std::string)ASSET_PATH + "minimize.wav", 0.4f, false);
			play_shrink_sound = false;
		}
	}
	else if (expanded == true) {
		graphics::Brush br;				// expanded box draw when hovered upon
		//draw the box
		br.fill_color[0] = 28.f / 255;
		br.fill_color[1] = 28.f / 255;
		br.fill_color[2] = 28.f / 255;
		br.outline_opacity = 0.4f;
		br.fill_opacity = 1;
		graphics::drawRect(pos_x, pos_y, expanded_width, height, br);
		//draw the text
		br.fill_color[0] = 0;
		br.fill_color[1] = 0;
		br.fill_color[2] = 0;
		br.outline_opacity = 0;
		br.fill_opacity = 1;
		graphics::drawText(700, 70, 17, "Genres: ", br);
		graphics::drawText(700, 170, 16, "From : ", br);
		graphics::drawText(700, 200, 16, "To       : ", br);
		br.fill_color[0] = 51 / 256.f;
		br.fill_color[1] = 48 / 256.f;
		br.fill_color[2] = 79 / 256.f;
		br.fill_opacity = 0.85f;
		graphics::drawText(760, 230, 12, "Movies found: ", br);
		graphics::drawText(840, 230, 12, std::to_string(movielist->FilteredMoviesAmount()), br);
		play_shrink_sound = true;
		if (play_expand_sound) {
			graphics::playSound((std::string)ASSET_PATH + "maximize.wav", 0.4f, false);
			play_expand_sound = false;
		}
	}
	graphics::resetPose();
	for (auto filter : filters) { //draw the filters only when menu is expanded
		if (expanded) {
			filter->draw();
		}
	}

}

void HoverMenu::update()
{

	//obtain current mouse status
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	// first interaction with the menu expands it
	if (abs(mx - pos_x) <= width / 2 && abs(my - pos_y) <= height / 2 && expanded == false) {
		expanded = true;
	}
	// later interactions with the menu keeps it expanded
	else if (abs(mx - pos_x) <= expanded_width / 2 && abs(my - pos_y) <= height / 2 && expanded == true) {
		expanded = true;
	}
	// shrink menu to original size
	else {
		expanded = false;
	}
	for (auto filter : filters) { //only allow the filters to be used when menu is expanded
		if (expanded) {
			filter->update();
		}
	}
}

void HoverMenu::drawText()
{
	//drawing the word "filters" on the side of the box for clarity
	graphics::Brush br;
	graphics::setOrientation(90);
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 1.f;
	br.fill_color[2] = 1.f;
	br.fill_opacity = 0.75f;
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 90, 16,"F", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 75, 16, "i", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 60, 16, "l", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 45, 16, "t", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 30, 16, "e", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3 + 15, 16, "r", br);
	graphics::drawText(pos_x + 4, pos_y / 1.3, 16, "s", br);
	graphics::resetPose();
}

void HoverMenu::init()
{
	//create and insert genre filters
	Checkbox* action_filter = new Checkbox();
	action_filter->setPos(750, 90);
	action_filter->setSize(50, 20);
	action_filter->setText("action");
	action_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "action"));
	action_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "action"));
	filters.push_back(action_filter);

	Checkbox* drama_filter = new Checkbox();
	drama_filter->setPos(810, 90);
	drama_filter->setSize(50, 20);
	drama_filter->setText("drama");
	drama_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "drama"));
	drama_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "drama"));
	filters.push_back(drama_filter);

	Checkbox* crime_filter = new Checkbox();
	crime_filter->setPos(870, 90);
	crime_filter->setSize(50, 20);
	crime_filter->setText("crime");
	crime_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "crime"));
	crime_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "crime"));
	filters.push_back(crime_filter);

	Checkbox* history_filter = new Checkbox();
	history_filter->setPos(930, 90);
	history_filter->setSize(50, 20);
	history_filter->setText("history");
	history_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "history"));
	history_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "history"));
	filters.push_back(history_filter);

	Checkbox* adventure_filter = new Checkbox();
	adventure_filter->setPos(780, 120);
	adventure_filter->setSize(50, 20);
	adventure_filter->setText("adventure");
	adventure_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "adventure"));
	adventure_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "adventure"));
	filters.push_back(adventure_filter);

	Checkbox* fantasy_filter = new Checkbox();
	fantasy_filter->setPos(840, 120);
	fantasy_filter->setSize(50, 20);
	fantasy_filter->setText("fantasy");
	fantasy_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "fantasy"));
	fantasy_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "fantasy"));
	filters.push_back(fantasy_filter);

	Checkbox* scifi_filter = new Checkbox();
	scifi_filter->setPos(900, 120);
	scifi_filter->setSize(50, 20);
	scifi_filter->setText("scifi");
	scifi_filter->addActionCallback1(std::bind(&MovieList::addGenreFilter, movielist, "scifi"));
	scifi_filter->addActionCallback2(std::bind(&MovieList::removeFilter, movielist, "scifi"));
	filters.push_back(scifi_filter);

	Slider* year_from = new Slider();
	year_from->setPos(842, 167);
	year_from->setSize(100, 1);
	year_from->setStart(1972);
	year_from->setEnd(2022);
	year_from->setPointer(0);
	year_from->addActionCallback(std::bind(&MovieList::changeYearFrom, movielist, std::placeholders::_1));
	filters.push_back(year_from);

	Slider* year_to = new Slider();
	year_to->setPos(842, 197);
	year_to->setSize(100, 1);
	year_to->setStart(1972);
	year_to->setEnd(2022);
	year_to->setPointer(1);
	year_to->addActionCallback(std::bind(&MovieList::changeYearTo, movielist, std::placeholders::_1));
	filters.push_back(year_to);

}
