#pragma once
#include "clickable.h"
#include <functional>

class TextField final : public Clickable {
	std::string data = "Search for movie...";
	std::string displayText = "Search for movie...";
	bool reset_data = true;
	bool typing_state = false;
	std::function<void(std::string)> action_callback = nullptr;
public:

	void update() override;
	void draw() override;
	char readChar();
	std::string getData();
	void addActionCallback(const std::function<void(std::string)> cb);
	TextField();
	~TextField();
};