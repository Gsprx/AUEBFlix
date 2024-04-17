#include "movie.h"
#include "graphics.h"
#include "config.h"
#include <string>

void Movie::draw()		// draw film data
{	
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.5f;

	graphics::setFont("assets\\DejaVuSansMono-Bold.ttf");
	graphics::drawText(CANVAS_WIDTH /20, CANVAS_HEIGHT / 5, 27, this->getName() ,br);


	graphics::setFont("assets\\cmb10.ttf");
	graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 3.6, 17, "Director: "+this->getDirector(), br);
	graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 3.1, 17, "Stars: "+this->getCharacters(), br);
	graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 2.7, 17, "Year: "+this->getDate(), br);
	graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 2.4, 17, "Genre: "+ this->getGenre(), br);

	graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT /1.90, 22, "Summary", br);
	this->getText();


}

void Movie::update() {}

void Movie::getText()
{
    {
        graphics::Brush br;
        br.outline_opacity = 0.0f;
        br.fill_opacity = 0.5f;
        std::string s1 = "";
        std::string s2 = "";
        std::string s3 = "";

        bool full = false; //if s1 is full
        bool full_2 = false; //if s2 is full
        bool full_3 = false; //if s2 is full
        int words = 0;
        int c = 0;
        int lenOfText = text.size();
        while (c < lenOfText) {
            if (c <= 90) {
                s1 += text[c];
                c++;
                if (c == 90) {
                    if (text[c + 1] != ' ') {
                        while (text[c] != ' ') {
                            s1 += text[c];
                            c++;
                        }//while
                    }
                }
            }
            else if (c <= 180) {
                s2 += text[c];
                c++;
                if (c == 180) {
                    if (text[c + 1] != ' ') {
                        while (text[c] != ' ') {
                            s2 += text[c];
                            c++;
                        }//while
                    }
                }
            }
            else {
                s3 += text[c];
                c++;
            }//else

        }//while

        graphics::setFont("assets\\cmb10.ttf");
        graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 1.8 + 5, 16, s1, br);
        graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 1.7 + 6, 16, s2, br);
        graphics::drawText(CANVAS_WIDTH / 24, CANVAS_HEIGHT / 1.62 + 8, 16, s3, br);
    }
}
