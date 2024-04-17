#include "screenshotlist.h"
#include "button.h"

void ScreenShotList::addMovieList(MovieList* ml)
{
	this->ml = ml;
}

void ScreenShotList::addHoverMenu(HoverMenu* hm)
{
	this->hm = hm;
}

void ScreenShotList::scroll_left()
{
	if (index == 0) {
		index = current_movie->screenshots.size() - 1;

	}
	else {
		index--;
	}
}

void ScreenShotList::scroll_right()
{
	if (index == current_movie->screenshots.size() - 1) {
		index = 0;
	}
	else {
		index++;
	}
}

void ScreenShotList::draw()
{
	if (current_movie == nullptr) {
		return;
	}

	graphics::Brush br;
	br.outline_opacity = 1;
	br.outline_width = 2;
	br.outline_color[0] = 1;
	br.outline_color[1] = 1;
	br.outline_color[2] = 1;
	br.texture = (std::string)ASSET_PATH + current_movie->screenshots[index];
	graphics::drawRect(pos_x, pos_y, width, height, br);

	if (hm->getExpandedStatus() == false) {
		shots_left->draw();
		shots_right->draw();
	}

}

void ScreenShotList::update()
{
	//update the screenshotlist when movielist changes
	Movie* prev = current_movie;
	Movie* next = ml->getCurrentMovie();
	if (prev != next) {
		index = 0;
		current_movie = next;
	}
	if (hm->getExpandedStatus() == false) {
		shots_left->update();
		shots_right->update();
	}
}

void ScreenShotList::init()
{
	shots_left = new Button();
	shots_left->setIcon("arrow.png");
	shots_left->setPos(pos_x - width / 2 + 10, pos_y);
	shots_left->setSize(35, 35);
	shots_left->addActionCallback(std::bind(&ScreenShotList::scroll_left, this));

	shots_right = new Button();
	shots_right->setIcon("arrow.png");
	shots_right->setPos(pos_x + width / 2 - 10, pos_y);
	shots_right->setSize(35, 35);
	shots_right->setOrientation(180);
	shots_right->addActionCallback(std::bind(&ScreenShotList::scroll_right, this));
}

ScreenShotList::ScreenShotList()
{
}

ScreenShotList::~ScreenShotList()
{
}

