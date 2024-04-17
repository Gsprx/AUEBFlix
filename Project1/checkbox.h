#pragma once
#include "clickable.h"
#include <functional>

class Checkbox final: public Clickable {
	bool checked = false;
	std::string text;
	std::function<void(std::string&)> action_callback1 = nullptr;
	std::function<void(std::string&)> action_callback2 = nullptr;
public:
	void draw() override;
	void update() override;

	void addActionCallback1(const std::function<void(std::string&)> cb1);
	void addActionCallback2(const std::function<void(std::string&)> cb2);
	bool getChecked();
	void setChecked(bool c);
	void setText(const std::string& t);
	std::string getText();
};