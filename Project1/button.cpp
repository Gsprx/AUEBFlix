#include "button.h"
#include "graphics.h"
#include "config.h"

void Button::draw()
{
										// determine draw orientation
	if (orientation != NULL) {
		graphics::setOrientation(orientation);
	}
	graphics::Brush br;					// normal draw when not highlighted
	br.texture = getIcon();
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 51.f / 255;
	br.fill_color[1] = 45.f / 255;
	br.fill_color[2] = 55.f / 255;
	br.fill_opacity = 0.25f;
	graphics::drawRect(pos_x, pos_y, width, height, br);


	if (highlighted) {	
		graphics::Brush br;				// lighter-gray draw when highlighted
		br.fill_color[0] = 197.f / 255;
		br.fill_color[1] = 186.f / 255;
		br.fill_color[2] = 212.f / 255;
		br.texture = getIcon();
		br.outline_opacity = 0.0f;
		br.fill_opacity = 0.75f;
		graphics::drawRect(pos_x, pos_y, width, height, br);

		if (interacted) {
			graphics::playSound((std::string)ASSET_PATH + "button.wav", 0.4f, false );
		}
	}
	graphics::resetPose();
}

void Button::update()
{
	//obtain current mouse status
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	//if mouse in close range become highlighted, if also pressed become interacted with
	if (abs(mx - pos_x) <= width / 3 && abs(my - pos_y) <= height / 3) {
		setHighlighted(true);
		if (ms.button_left_pressed) {
			setInteracted(true);
			if (action_callback) {	//if action callback pointer not nullptr, execute
				action_callback();
			}
		}
		else {
			setInteracted(false);
		}
	}
	else {
		setInteracted(false);
		setHighlighted(false);
	}
}

void Button::addActionCallback(const std::function<void()> cb)
{
	action_callback = cb;
}

Button::Button()
{
}

Button::~Button()
{
}

