#include "checkbox.h"
#include "graphics.h"
#include "config.h"

void Checkbox::draw()
{
	graphics::Brush br;		//normal draw when not checked
	//draw the box
	br.outline_opacity = 0.7f;
	br.outline_color[0] = 76.f / 255;
	br.outline_color[1] = 79.f / 255;
	br.outline_color[2] = 84.f / 255;
	br.fill_color[0] = 158.f / 255;
	br.fill_color[1] = 166.f / 255;
	br.fill_color[2] = 181.f / 255;
	br.fill_opacity = 0.7f;
	graphics::drawRect(pos_x, pos_y, width, height, br);
	//draw the text
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.f;
	br.fill_color[1] = 0.f;
	br.fill_color[2] = 0.f;
	br.fill_opacity = 1;
	float text_offset = 0;
	//draw text based on the length of text string
	if (text.size() <= 7) {
		text_offset = 11 - text.size();
	}
	graphics::drawText(pos_x - 25 + text_offset, pos_y + 5, 10, text, br);

	if (interacted) {
		graphics::playSound((std::string)ASSET_PATH + "button.wav", 0.4f, false);
	}
	if (checked) {
		//green draw when checked
		br.fill_color[0] = 54.f / 255;
		br.fill_color[1] = 145.f / 255;
		br.fill_color[2] = 78.f / 255;
		graphics::drawRect(pos_x, pos_y, width - 1, height - 1, br);
	}
}

void Checkbox::update()
{
	//obtain current mouse status
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	//if mouse in close range become highlighted, if also pressed become interacted with
	if (abs(mx - pos_x) <= width / 2 && abs(my - pos_y) <= height / 2) {
		if (ms.button_left_pressed) {
			if (checked == false) {
				setChecked(true);
				action_callback1(text);	//only call back 1 when switching states
			}
			else if (checked == true) {
				setChecked(false);
				action_callback2(text); //only call back 2 when switching states
			}
			setInteracted(true);
		}
		else {
			setInteracted(false);
		}
	}
}

void Checkbox::addActionCallback1(const std::function<void(std::string&)> cb1)
{
	action_callback1 = cb1;
}

void Checkbox::addActionCallback2(const std::function<void(std::string&)> cb2)
{
	action_callback2 = cb2;
}

bool Checkbox::getChecked()
{
    return checked;
}

void Checkbox::setChecked(bool c)
{
	checked = c;
}

void Checkbox::setText(const std::string& t)
{
	text = t;
}

std::string Checkbox::getText()
{
	return text;
}


