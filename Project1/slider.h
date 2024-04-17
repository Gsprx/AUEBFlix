#pragma once
#include "draggable.h"
#include <functional>

class Slider final: public Draggable {
	int start_value = 0;
	int end_value = 100;
	float pointer_pos = 0.f;  //between 0-100% across the bar's length 
	unsigned int pointer_x = 0.5f;
	std::function<void(int)> action_callback = nullptr;

public:
	void update();
	void draw();
	void addActionCallback(const std::function<void(int)> cb);
	int getValue();
	void setStart(int s);
	void setEnd(int e);
	void setPointer(float p);

	Slider();
	~Slider();
};