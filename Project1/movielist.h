#pragma once
#include "Movie.h"
#include "widget.h"
#include <vector>

class MovieList : public Widget{
	std::vector<Movie*> movies; //starting array of all movies
	std::vector<Movie*> current_movies; //vector that includes only filtered movies
	std::vector<std::string> genre_filters;
	std::string title_filter = "";
	int index = 0;
	int year_from;
	int year_to;

public:

	Movie* getCurrentMovie();
	int FilteredMoviesAmount();
	void changeYearTo(int t);
	void changeYearFrom(int f);
	void scroll_left();
	void scroll_right();
	void update() override;
	void draw() override;
	void init();
	void addGenreFilter(const std::string& filter);
	void removeFilter(const std::string& filter);
	void updateList();
	void changeTitleFilter(const std::string& title);
	
	MovieList();
	~MovieList();
};