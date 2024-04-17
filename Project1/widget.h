#pragma once
#include <string>

class Widget {
protected:
	unsigned int pos_x;				
	unsigned int pos_y;				
	unsigned int width;				
	unsigned int height;			
	int orientation = 0;			
	bool highlighted = false;	
	bool interacted = false;
	std::string icon;
	


public:
	
	virtual void draw() = 0;
	virtual void update() = 0;

	void setInteracted(bool i);
	void setHighlighted(bool h);
	void setPos(unsigned int x, unsigned int y);
	void setIcon(const std::string& icon_name);
	void setSize(unsigned int w, unsigned int h);
	void setOrientation(int o);
	std::string getIcon();
};