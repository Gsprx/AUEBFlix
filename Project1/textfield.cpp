#include "textfield.h"
#include "graphics.h"
#include "config.h"
#include "movielist.h"

void TextField::update()
{
    //obtain current mouse status
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    //if mouse is pressed inside of the box, allow and record typing
    if (abs(mx - pos_x) <= width /2 && abs(my - pos_y) <= height /2 && ms.button_left_pressed) {
        typing_state = true;

    }
    //if mouse is still inside of the box, keep recording typing
    else if (abs(mx - pos_x) <= width / 2 && abs(my - pos_y) <= height / 2){
        if (typing_state) {
            typing_state = true;
        }
    }
    else {
        typing_state = false;
    }

    if (typing_state) {
        if (data._Equal("Search for movie...") && reset_data) {
            data = "";
            reset_data = false;
        }
        //append string with read char
        char ch = readChar();
        if (ch != 0) {
            data += ch;
            if (ch == 8) {
                if (data.size() - 1 > 0) {
                    data.resize(data.size() - 2);
                }
                else {
                    data.resize(0);
                }
            }
            action_callback(data);
        }
    }
    else if (data._Equal("")) {
        data = "Search for movie...";
        reset_data = true;
    }


}

void TextField::draw()
{
    graphics::Brush br;					

    //drawing the box-field
    br.outline_opacity = 1.f;
    br.fill_color[0] = 1;
    br.fill_color[1] = 1;
    br.fill_color[2] = 1;
    br.outline_color[0] = 0;
    br.outline_color[1] = 0;
    br.outline_color[2] = 0;
    br.fill_opacity = 0.65f;
    graphics::drawRect(pos_x, pos_y, width, height, br);

    if (data.size() < 30) {
        displayText = data;
    }
    else {
        displayText = "";
        for (int i = 30; i > 0; i--) {
            displayText += data[data.size() - i];
        }
    }

    //drawing the typed text inside the box
    br.outline_opacity = 1.f;
    br.fill_color[0] = 0;
    br.fill_color[1] = 0;
    br.fill_color[2] = 0;
    br.outline_color[0] = 0;
    br.outline_color[1] = 0;
    br.outline_color[2] = 0;
    
    if (displayText._Equal("Search for movie...")) {
        graphics::setFont((std::string)ASSET_PATH + "STIXGeneralItalic.ttf");
        br.fill_opacity = 0.55f;
    }
    else {
        graphics::setFont((std::string)ASSET_PATH + "cmb10.ttf");
        br.fill_opacity = 1.f;
    }
    
    graphics::drawText(pos_x - (width / 2) + 2, pos_y + 5, 14, displayText, br);

}

char TextField::readChar()
{
    static float delay = 0.0f;
    static int prev = 0;
    char ascii = 0;
    delay += graphics::getDeltaTime();

    for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_SPACE; i++) {
        if (graphics::getKeyState((graphics::scancode_t)i)) {
            if (prev == i && delay < 200) {
                continue;
            }
            else {
                prev = i;
                delay = 0;

                //if letters
                if (i >= graphics::SCANCODE_A && i <= graphics::SCANCODE_Z) {
                    ascii = (char)(i + 93);
                    //if letters in caps
                    if (graphics::getKeyState(graphics::SCANCODE_RSHIFT) || graphics::getKeyState(graphics::SCANCODE_LSHIFT)) {
                        ascii -= 32;
                    }
                }
                //if numbers
                if (i >= graphics::SCANCODE_1 && i <= graphics::SCANCODE_0) {
                    //zero is not in proper order, checking seperately
                    if (i == graphics::SCANCODE_0) {
                        ascii = (char)(48);
                    }
                    else {
                        ascii = (char)(i + 19);
                    }
                }
                //if special characters
                    //backspace
                if (i == graphics::SCANCODE_BACKSPACE) {
                    ascii = (char)(8);
                }
                    //space
                if (i == graphics::SCANCODE_SPACE) {
                    ascii = (char)(32);
                }
                    //hyphen-minus
                if (i == graphics::SCANCODE_MINUS) {
                    ascii = (char)(45);
                }
                    //colon
                if (i == graphics::SCANCODE_SEMICOLON) {
                    if (graphics::getKeyState(graphics::SCANCODE_RSHIFT) || graphics::getKeyState(graphics::SCANCODE_LSHIFT)) {
                        ascii = (char)58;
                    }
                }
            }
        }
    }
    return ascii;
}

std::string TextField::getData()
{
    return data;
}

void TextField::addActionCallback(const std::function<void(std::string)> cb)
{
    action_callback = cb;
}

TextField::TextField()
{
}

TextField::~TextField()
{
}
