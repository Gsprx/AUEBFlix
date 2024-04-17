#pragma once
using namespace std;
#include <string>
#include "config.h"
#include "graphics.h"
#include <vector>




class Movie {
private:
	
	string name;
	string production_date;
	string director;
	string main_characters;
	string genre;
	string image;
	string text;

public:

	vector<string>screenshots;
	void draw();
	void update();
	void getText();

	//Constructor
	Movie(const string& moviename, const string& pr_date,
		const string& dir, const string& main_charact, const string& k, const string& im, const string& txt)
	{
		name = moviename;
		production_date = pr_date;
		director = dir;
		main_characters = main_charact;
		genre = k;
		image = im;
		text = txt;
	}
	void addScreenshot(const string& ss) {
		screenshots.push_back(ss);
	}

	string getName() {
		return name;
	}

	string getDate() {
		return production_date;
	}

	string getDirector() {
		return director;
	}

	string getCharacters() {
		return main_characters;
	}

	string getGenre() {
		return genre;
	}

	string getImage() {
		return image;
	}


};