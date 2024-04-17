#pragma once
#include "clickable.h"
#include <functional>

class Button final : public Clickable {
	std::function<void()> action_callback = nullptr;
public:
	void addActionCallback(const std::function<void()> cb);
	void draw() override;
	void update() override;
	
	Button();
	~Button();

};