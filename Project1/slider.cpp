#include "slider.h"
#include "config.h"
#include "graphics.h"

void Slider::draw()
{
	graphics::setFont((std::string)ASSET_PATH + "cmb10.ttf"); 

	//draw the silder bar first
	graphics::Brush br;
	br.fill_opacity = 1.f;
	br.outline_opacity = 0.7f;
	br.outline_color[0] = 76.f / 255;
	br.outline_color[1] = 79.f / 255;
	br.outline_color[2] = 84.f / 255;
	br.fill_color[0] = 158.f / 255;
	br.fill_color[1] = 166.f / 255;
	br.fill_color[2] = 181.f / 255;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	//draw the slider's min/max values
	br.outline_opacity = 0.f;
	br.fill_color[0] = 158.f / 255;
	br.fill_color[1] = 166.f / 255;
	br.fill_color[2] = 181.f / 255;
	graphics::drawText(pos_x - width * 0.5 - 35, pos_y + 3, 14, std::to_string(start_value), br);
	graphics::drawText(pos_x + width * 0.5 + 5, pos_y + 3, 14, std::to_string(end_value), br);

	//draw the slider's pointer second
	br.fill_color[0] = 10 / 255.f;
	br.fill_color[1] = 2 / 255.f;
	br.fill_color[2] = 25 / 255.f;
	graphics::drawRect(pointer_x, pos_y, 7, 20, br);

	//draw the current value of the slider above the pointer
	br.fill_color[0] = 1;
	br.fill_color[1] = 1;
	br.fill_color[2] = 1;
	graphics::drawText(pointer_x - 11, pos_y - 15, 12, std::to_string(getValue()), br);

	
}

void Slider::addActionCallback(const std::function<void(int)> cb)
{
	action_callback = cb;
}

void Slider::update()
{
	//obtain current and previous mouse status
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	//update slider pointer potision
	if (distance(mx, my, pointer_x, pos_y) <= 5 && ms.button_left_pressed) {
		graphics::playSound((std::string)ASSET_PATH + "browse.wav", 0.1);
	}
	if (distance(mx, my, pointer_x, pos_y) <= 5 && ms.button_left_down) {
		if (mx < pos_x - width * 0.5) {			//
			pointer_x = pos_x - width * 0.5;	// restrict movement only across the 
		}										// bar's 2 ends (min_x / max_x)
		else if (mx > pos_x + width * 0.5) {	// 
			pointer_x = pos_x + width * 0.5;	//
		}										//
		else {
			pointer_x = mx;
		}
	}
	//update slider value based on position
	pointer_pos = (pointer_x - (pos_x - width * 0.5)) / width;
	action_callback(getValue());

}

int Slider::getValue()
{	//calculates the value of the slider pointer
	int dist = end_value - start_value;
	return pointer_pos == 0 ? start_value : floor(start_value + dist * pointer_pos);
}

void Slider::setStart(int s)
{
	start_value = s;
}

void Slider::setEnd(int e)
{
	end_value = e;
}

void Slider::setPointer(float p)
{
	pointer_pos = p;
	pointer_x = pos_x - width * 0.5 + width * (pointer_pos);
}

Slider::Slider()
{
}

Slider::~Slider()
{
}

