#include "movielist.h"
#include <vector>
#include <cctype>
#include <algorithm>

Movie* MovieList::getCurrentMovie()
{
	return current_movies.size() != 0 ? current_movies[index] : nullptr;
}

int MovieList::FilteredMoviesAmount()
{
	return current_movies.size();
}

void MovieList::changeYearTo(int t)
{
	year_to = t;
}

void MovieList::changeYearFrom(int f)
{
	year_from = f;
}

void MovieList::scroll_left()
{
	if (index == 0) {
		index = current_movies.size() - 1;

	}
	else {
		index--;
	}
}

void MovieList::scroll_right()
{
	if (index == current_movies.size() - 1) {
		index = 0;
	}
	else {
		index++;
	}
}

void MovieList::update()
{
	int prev_size = (int)current_movies.size();
	updateList();
	int current_size = (int)current_movies.size();

	if (prev_size != current_size) {
		index = 0;
	}
}

void MovieList::draw()
{


	graphics::Brush br;
	br.fill_color[0] = 0.200f;	//set the color of the background
	br.fill_color[1] = 0.165f;
	br.fill_color[2] = 0.174f;
	br.outline_opacity = 0.0f;
	int current_size = (int)current_movies.size();

	if (current_size > 4) {													//
																		// case of 5 or more movies is able to loop them using 5 movies, perfect smoothness
																		//
		float movement[5] = { 6.5, 3.12, 2, 1.475, 1.185 };
		int m_counter = 0; //movement array counter
		int temp; //temporary variable that offsets the index to a real usable one
		//loop set around -2,+2 offset of index
		for (int i = -2; i < 3; i++) {

			temp = index + i;
			if (temp < 0) {
				temp = current_size + temp;
			}
			else if (temp > current_size - 1) {
				temp = temp - current_size;
			}

			graphics::Brush br;
			if (temp == index) {		//highlight selected movie with high outline and draw its contents
				br.outline_opacity = 1.f;
				br.outline_color[0] = 1.f;
				br.outline_color[1] = 1.f;
				br.outline_color[2] = 1.f;
				current_movies[temp]->draw();
			}
			else {
				br.outline_opacity = 0.0f;
			}

			br.texture = string(ASSET_PATH) + current_movies[temp]->getImage();
			br.fill_opacity = 0.5f;
			if (i == 0) {
				graphics::drawRect(CANVAS_WIDTH / movement[m_counter], CANVAS_HEIGHT / 1.2, 170, 130, br);
			}
			else {
				graphics::drawRect(CANVAS_WIDTH / movement[m_counter], CANVAS_HEIGHT / 1.2, 150, 100, br);

			}
			m_counter++;
		}
	}
	else if (current_size > 2) {							    //
															//	case of 3-4 movies is able to loop using 3 movies, not as smooth and realistic
															//
		float movement[3] = { 3.12, 2, 1.475 };
		int m_counter = 0; //movement array counter
		int temp; //temporary variable that offsets the index to a real usable one
		//loop set around -1,+1 offset of index

		for (int i = -1; i < 2; i++) {

			temp = index + i;

			//always stay within limits - pseudo loop
			if (temp < 0) {
				temp = current_size + temp;
			}
			else if (temp > current_size - 1) {
				temp = temp - current_size;
			}

			graphics::Brush br;
			if (temp == index) {		//highlight selected movie with high outline and draw its contents
				br.outline_opacity = 1.f;
				br.outline_color[0] = 1.f;
				br.outline_color[1] = 1.f;
				br.outline_color[2] = 1.f;
				current_movies[temp]->draw();
			}
			else {
				br.outline_opacity = 0.0f;
			}

			br.texture = string(ASSET_PATH) + current_movies[temp]->getImage();
			br.fill_opacity = 0.5f;
			if (i == 0) {
				graphics::drawRect(CANVAS_WIDTH / movement[m_counter], CANVAS_HEIGHT / 1.2, 170, 130, br);
			}
			else {
				graphics::drawRect(CANVAS_WIDTH / movement[m_counter], CANVAS_HEIGHT / 1.2, 150, 100, br);

			}
			m_counter++;
		}
	}
	else if (current_size > 0) {							// 
														// case of 2 or 1 movies, unable to loop them at all, can only switch them to emulate the "loop"
														//

		graphics::Brush br;
		//highlight selected movie with high outline and draw its contents
		br.outline_opacity = 1.f;
		br.outline_color[0] = 1.f;
		br.outline_color[1] = 1.f;
		br.outline_color[2] = 1.f;
		current_movies[index]->draw();

		br.texture = string(ASSET_PATH) + current_movies[index]->getImage();
		br.fill_opacity = 0.5f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.2, 170, 130, br);
	}
	else {											//
													// case of no movies, simply show a relative message on screen
													//
		graphics::Brush br;
		br.outline_opacity = 1.f;
		br.outline_color[0] = 1.f;
		br.outline_color[1] = 1.f;
		br.outline_color[2] = 1.f;
		graphics::setFont((std::string)ASSET_PATH + "STIXGeneralItalic.ttf");
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2.5f, 24, "No Movies found!", br);
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2.f, 20, "Try changing the filters...", br);
	}
}

void MovieList::init()
{
	//initializing movies with data and screenshots
	//fight club
	Movie* fightclub = new Movie("Fight Club", "1999", "David Ficher", "Brad Pitt,Edward Norton, Helena Bonham Carter", "drama", "FightClub.png", "An isomniac office worker and a devil-may care soap maker form an underground fight club that evolves into much more.");
	fightclub->addScreenshot("shot-FightClubV1.png");
	fightclub->addScreenshot("shot-FightClubV2.png");
	//sci-fighter
	Movie* scifighter = new Movie("Sci-Fighter","2004","Art Camacho","Don Wilson, Cynthia Rothrock, Lorenzo Lamas"," action, scifi","SciFighter.png","A computer virus has invaded a virtual reality fighting game leaving a rebellious teen trapped within. Now the boy's father must enter the tainted program and battle his way through a deadly maze of martial arts fighters to save his son.");
	scifighter->addScreenshot("shot-SciFighterV1.png");
	scifighter->addScreenshot("shot-SciFighterV2.png");
	scifighter->addScreenshot("shot-SciFighterV3.png");
	//the godfather
	Movie* godfather = new Movie("The Godfather", "1972", "Francis Ford Coppola", "Marlon Brando, Al Pacino, James Caan", "drama, history", "Godfather.png", "The aging patriarch of an organized dynasty in postwar New York City transfers control of his clandestine empire to his reluctant youngest son.");
	godfather->addScreenshot("shot-GodfatherV1.png");
	//the terminator
	Movie* terminator = new Movie("The Terminator", "1984", "James Cameron", "Arnold Schwarzenegger, Linda Harniton, MichaelBiehn ", "scifi, action", "Terminator.png", "A human soldier is sent from 2029 to 1984 to stop an almost indestructible cyborg killing machine sent from the same year, which has been programmed to execute a young woman whose unborn son is the key to humanity fure salvation.");
	terminator->addScreenshot("shot-TerminatorV1.png");
	terminator->addScreenshot("shot-TerminatorV2.png");
	terminator->addScreenshot("shot-TerminatorV3.png");
	//pulp fiction
	Movie* pulpfiction = new Movie("Pulp Fiction", "1994", "Quertin Tarantino", "John Travolta, Samuel Jackson, Uma Thurman ", "drama, crime", "PulpFiction.png", "The lives of two mob hitmen a boxer a gangster and his wife, and a pair of dinner bandits inter twine in four tales of violence and redemption.");
	pulpfiction->addScreenshot("shot-PulpFictionV1.png");
	pulpfiction->addScreenshot("shot-PulpFictionV2.png");
	pulpfiction->addScreenshot("shot-PulpFictionV3.png");
	//schindlers list
	Movie* schindlerslist = new Movie("Schindlers List", "1993", " Steven Spielberg", "Ben Kingsley,Liam Neeson, Ralph Fiennes", "drama ,history", "SchindlersList.png", "In German occupied Poland during World War II industrials Oskar Schindler gradually becomes concerned for his Jewish work force after witnessing their persecution by the Nazis.");
	schindlerslist->addScreenshot("shot-SchindlersListV1.png");
	schindlerslist->addScreenshot("shot-SchindlersListV2.png");
	schindlerslist->addScreenshot("shot-SchindlersListV3.png");
	//starwars a new hope
	Movie* starwarsIV = new Movie("Star Wars: Episode IV - A New Hope", "1977", "    George Lucas", "Carrier Fisher, Harrison Ford, Mark Hamill", "adventure, action, fantasy", "ANewHope.png",
		"Luke Skywalker joins forces with a Jedi Knight a cocky pilot a Wookiee and two droids to save the galaxy from the Empire's worldestroying battle station while also attempting to rescue Princess Leia from the mysterious Darth Vader.");
	starwarsIV->addScreenshot("shot-ANewHopeV1.png");
	starwarsIV->addScreenshot("shot-ANewHopeV2.png");
	starwarsIV->addScreenshot("shot-ANewHopeV3.png");
	//starwars the empire strikes back
	Movie* starwarsV = new Movie("Star Wars: Episode V - The Empire Strikes Back", "1980", "Irvin Kershner", "Mark Hamill, Harrison Ford, Carrie Fisher", "action, adventure, fantasy",
		"EmpireStrikesBack.png", "After the Rebels are brutally overpowered by the Empire on the planet Hoth Skywalker begins Jedi training with Yoda while his friends pursued across the galaxy by Darth Vader and bounty hunter Boba Fett.");
	starwarsV->addScreenshot("shot-StarWarsV1.png");
	starwarsV->addScreenshot("shot-StarWarsV2.png");
	starwarsV->addScreenshot("shot-StarWarsV3.png");
	starwarsV->addScreenshot("shot-StarWarsV4.png");
	starwarsV->addScreenshot("shot-StarWarsV5.png");
	starwarsV->addScreenshot("shot-StarWarsV6.png");
	//raiders of the lost ark
	Movie* raidersofthelostark = new Movie("Indiana Jones and the Raiders of the Lost Ark", "1981", "Steven Spieberg", "Harrison Ford, Karen Alen, Paul Freeman", "adventure, action", "RaidersOfTheLostArk.png", "Archaeology protessor jONES venture to seize a biblical artfact known as the Ark of Conevant. While doings so he puts up a fight against Renee and a troop of Nazis.");
	raidersofthelostark->addScreenshot("shot-RaidersOfTheLostArkV1.png");
	raidersofthelostark->addScreenshot("shot-RaidersOfTheLostArkV2.png");
	raidersofthelostark->addScreenshot("shot-RaidersOfTheLostArkV3.png");
	raidersofthelostark->addScreenshot("shot-RaidersOfTheLostArkV4.png");
	//wednesday
	Movie* wednesday= new Movie("Wednesday", "2022", "Alfred Gough Miles Millor", "Jenna Ortega", "comedy,horror,supernatural", "wednesday.png", "Wednesday is an American coming of age supernatural comedy horro streaming television series based on the character Wednesday Addams by Charles Addams.");
	wednesday->addScreenshot("shot-wednesdayV1.png");
	wednesday->addScreenshot("shot-wednesdayV2.png");
	wednesday->addScreenshot("shot-wednesdayV3.png");
	//split
	Movie* split = new Movie("Split", "2016", "M. Night Shyamalan", "James McAvoy", "supernatural,psychological,horror", "split.png", "Split is a 2016 American supernatural psychological horror film written directed and produced by M. Night Shyamalan and starring James McAvoy, Anya Taylor-Joy and Betty Buckley.");
	split->addScreenshot("shot-splitV1.png");
	split->addScreenshot("shot-splitV2.png");
	split->addScreenshot("shot-splitV3.png");
	//nanny
	Movie* nanny = new Movie("Nanny", "2022", "Nikyatu Jusu", "Anna Diop", "horror", "Nanny.png", "Nanny is an American horror film written and directed by Nikyatu Jusu in her feature directional debut.");
	nanny->addScreenshot("shot-NannyV1.png");
	nanny->addScreenshot("shot-NannyV2.png");
	nanny->addScreenshot("shot-NannyV3.png");
	nanny->addScreenshot("shot-NannyV4.png");
	//lord of the rings
	Movie* Lord = new Movie("Lord of the Rings: The Two Towers","2002","Peter Jackson","Elijah Wood, Ian McKellen,  Viggo Mortensen"," adventure, action, drama","LordOfTheRings.png","While Frodo and Sam edge closer to Mordor with the help of shifty Gollum the divided fellowship makes a stand against Sauron's new ally Saruman and his hordes of Isengard");
	Lord->addScreenshot("shot-LordOfTheRingsV1.png");
	Lord->addScreenshot("shot-LordOfTheRingsV2.png");
	Lord->addScreenshot("shot-LordOfTheRingsV3.png");
	Lord->addScreenshot("shot-LordOfTheRingsV4.png");
	//the lion king
	Movie* LionKing = new Movie("The Lion King","1994","Roger Allers, Rob Minkoff","Matthew Broderick, Jeremy Irons, James Earl Jones"," animation, adventure, drama","TheLionKing.png","Lion prince Simba and his father are targeted by his bitter uncle who wants to ascend the throne himself.");
	LionKing->addScreenshot("shot-TheLionKingV1.png");
	LionKing->addScreenshot("shot-TheLionKingV2.png");
	LionKing->addScreenshot("shot-TheLionKingV3.png");
	LionKing->addScreenshot("shot-TheLionKingV4.png");
	//avatar
	Movie* avatar = new Movie("Avatar: The Way of Water","2022" ,"James Cameron","Sam Worthington, Zoe Saldana, Sigourney Weaver"," action, adventure, fantasy", "Avatar.png", "Jake Sully lives with his newfound family formed on the extrasolar moon Pandora.Once a familiar threat returns to finish what was previously started Jake must work with Neytiri and the army of the Na'vi race to protect their home.");
	avatar->addScreenshot("shot-AvatarV1.png");
	avatar->addScreenshot("shot-AvatarV2.png");
	avatar->addScreenshot("shot-AvatarV3.png");
	avatar->addScreenshot("shot-AvatarV4.png");
	//knives out
	Movie* knives = new Movie("Knives out","2019","Rian Johnson","Daniel Craig, Chris Evans, Ana de Armas"," comedy, crime, drama","KnivesOut.png","A detective investigates the death of the patriarch of an eccentric combative family.");
	knives->addScreenshot("shot-KnivesOutV1.png");
	knives->addScreenshot("shot-KnivesOutV2.png");
	knives->addScreenshot("shot-KnivesOutV3.png");
	knives->addScreenshot("shot-KnivesOutV4.png");
	//titanic
	Movie* titanic = new Movie("Titanic","1997","James Cameron","Leonardo DiCaprio, Kate Winslet, Billy Zane"," drama, romance","Titanic.png","A seventeen-year-old aristocrat falls in love with a kind but poor artist aboard the luxurious ill-fated R.M.S. Titanic.");
	titanic->addScreenshot("shot-TitanicV1.png");
	titanic->addScreenshot("shot-TitanicV2.png");
	titanic->addScreenshot("shot-TitanicV3.png");
	titanic->addScreenshot("shot-TitanicV4.png");
	//home alone
	Movie* homealone = new Movie("Home Alone","1990","Chris Columbus","Macaulay Culkin, Joe Pesci, Daniel  Stern"," comedy, family","HomeAlone.png","An eight-year-old troublemaker, mistakenly left home alone, must defend his home against a pair of burglars on Christmas eve.");
	homealone->addScreenshot("shot-HomeAloneV1.png");
	homealone->addScreenshot("shot-HomeAloneV2.png");
	homealone->addScreenshot("shot-HomeAloneV3.png");
	homealone->addScreenshot("shot-HomeAloneV4.png");
	
	
	
	
	
	//insert movies into vector
	movies.push_back(fightclub);
	movies.push_back(godfather);
	movies.push_back(terminator);
	movies.push_back(pulpfiction);
	movies.push_back(schindlerslist);
	movies.push_back(starwarsIV);
	movies.push_back(starwarsV);
	movies.push_back(raidersofthelostark);
	movies.push_back(wednesday);
	movies.push_back(split);
	movies.push_back(nanny);
	movies.push_back(Lord);
	movies.push_back(LionKing);
	movies.push_back(avatar);
	movies.push_back(knives);
	movies.push_back(titanic);
	movies.push_back(homealone);
	movies.push_back(scifighter);
	//initialize min and max year values for sorting
	int min, max;
	min = max = std::stoi(movies[0]->getDate());
	for (auto movie : movies) {
		int date = std::stoi(movie->getDate());
		if (date > max) {
			max = date;
		}
		if (date < min) {
			min = date;
		}
	}
	year_to = max;
	year_from = min;
}


void MovieList::updateList()
{
	//empty previous filtered movies
	current_movies.clear();

	//start the filtering process
	for (auto movie : movies) {
		bool matching_genres = false;
		bool matching_year = false;
		bool matching_title = false;
		int genres_found = 0;
		//movie's genres comparison
			//if we have no filters, set matching_genres true
		if (genre_filters.size() == 0) {
			matching_genres = true;
		}
		//if we have at least 1 filter, search for them
		else {
			for (auto& filter : genre_filters) {
				if (movie->getGenre().std::string::find(filter) != std::string::npos) {		//checking if movie genres contain the current filter genre
					genres_found++;
				}
			}
			if (genres_found == genre_filters.size()) {
				matching_genres = true;
			}
		}
		//movie's year comparison
		if (std::stoi(movie->getDate()) >= year_from && std::stoi(movie->getDate()) <= year_to) {
			matching_year = true;
		}
		//movie's title comparison
			//if there is a title searched, look for it
		if (!title_filter._Equal("")) {
			std::string movie_name = movie->getName();
			std::string temp_filter = title_filter;
			//transform movie name and title filter to lowercase for a better comparison
			std::transform(movie_name.begin(), movie_name.end(), movie_name.begin(), [](unsigned char c) { return std::tolower(c); });
			std::transform(temp_filter.begin(), temp_filter.end(), temp_filter.begin(), [](unsigned char c) { return std::tolower(c); });

			if (movie_name.std::string::find(temp_filter) != std::string::npos) {
				matching_title = true;
			}
		}
		//if there is nothing typed, ignore this requirement
		else {
			matching_title = true;
		}

		//finally push suitable movies into current_movies if they are within the year sorting limits 
		if (matching_genres && matching_year && matching_title) {
			current_movies.push_back(movie);
		}
	}
}

void MovieList::changeTitleFilter(const std::string& title)
{
	title_filter = title;
}

void MovieList::addGenreFilter(const std::string& filter)
{
	genre_filters.push_back(filter);
}

void MovieList::removeFilter(const std::string& filter)
{
	for (int i = 0; i < genre_filters.size(); i++) {
		if (genre_filters[i].compare(filter) == 0) {
			genre_filters.erase(genre_filters.begin() + i);
		}
	}
}

MovieList::MovieList()
{
	init();
}

MovieList::~MovieList()
{
	for (auto movie : movies) {
		delete movie;
	}
	movies.clear();

}
