#include "graphics.h"
#include "filmbrowser.h"
#include "config.h"

void update(float ms)
{
    FilmBrowser* browser = reinterpret_cast<FilmBrowser*>(graphics::getUserData());
    browser->update();
}

void draw()
{
    FilmBrowser* browser = reinterpret_cast<FilmBrowser*>(graphics::getUserData());
    browser->draw();
}

int main()
{   //film browser window + filmbrowser pointer initialization
    FilmBrowser * mybrowser = new FilmBrowser;
      
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AUEBflix");

    graphics::setUserData(mybrowser);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::Brush br;                         //draw background 
    br.fill_color[0] = 10.f / 255.f;
    br.fill_color[1] = 0.f;
    br.fill_color[2] = 10.f / 255.f;			//set primary color (dark purple)

    graphics::setWindowBackground(br);
    graphics::startMessageLoop();

    graphics::destroyWindow();
    delete mybrowser;

    return 0;
}
