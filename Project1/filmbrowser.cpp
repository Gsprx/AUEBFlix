#include "filmbrowser.h"
#include "graphics.h"
#include "config.h"
#include "button.h"
#include "movielist.h"
#include "hovermenu.h"
#include "textfield.h"
#include "screenshotlist.h"

void FilmBrowser::update(){
	//call update for all widgets
	for (auto widget : widgets)
		widget->update();
	
}

void FilmBrowser::draw(){
	//call draw for all widgets
	for (auto widget : widgets)
		widget->draw();

}

void FilmBrowser::init(){
	movielist = new MovieList();
	movielist->updateList();
	widgets.push_back(movielist);

	Button* movies_left = new Button();
	movies_left->setIcon("arrow.png");
	movies_left->setPos(50, CANVAS_HEIGHT - 85);
	movies_left->setSize(60, 60);
	movies_left->addActionCallback(std::bind(&MovieList::scroll_left, movielist));
	widgets.push_back(movies_left);

	Button* movies_right = new Button();
	movies_right->setIcon("arrow.png");
	movies_right->setPos(CANVAS_WIDTH - 50, CANVAS_HEIGHT - 85);
	movies_right->setSize(60, 60);
	movies_right->setOrientation(180);
	movies_right->addActionCallback(std::bind(&MovieList::scroll_right, movielist));
	widgets.push_back(movies_right);

	ScreenShotList* shots_list = new ScreenShotList();
	shots_list->setPos(CANVAS_WIDTH * 0.8, CANVAS_HEIGHT * 0.32);
	shots_list->setSize(200, 200);
	shots_list->addMovieList(movielist);
	shots_list->init();

	HoverMenu* filter_menu = new HoverMenu();
	filter_menu->setMovieList(movielist);
	filter_menu->init();
	filter_menu->setPos(CANVAS_WIDTH * 0.99, 150);
	filter_menu->setSize(20, 200);
	filter_menu->setExpandedWidth(600);
	
	shots_list->addHoverMenu(filter_menu);
	widgets.push_back(shots_list);
	widgets.push_back(filter_menu);

	TextField* movie_search = new TextField();
	movie_search->setPos(145, 45);
	movie_search->setSize(200, 25);
	movie_search->addActionCallback(std::bind(&MovieList::changeTitleFilter, movielist, std::placeholders::_1));
	widgets.push_back(movie_search);


}


FilmBrowser::FilmBrowser(){
	init();
}

FilmBrowser::~FilmBrowser(){
	//destructor must delete all widget objects
	for (auto widget : widgets)
		delete widget;
	widgets.clear();
}
