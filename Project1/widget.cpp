#include "widget.h"
#include "graphics.h"
#include "config.h"

void Widget::setHighlighted(bool h)
{
    highlighted = h;
}

void Widget::setInteracted(bool i)
{
    interacted = i;
}

void Widget::setPos(unsigned int x, unsigned int y)
{
    pos_x = x;
    pos_y = y;
}

void Widget::setIcon(const std::string& icon_name)
{
    icon = (std::string)ASSET_PATH + icon_name;
}

std::string Widget::getIcon()
{
    return icon;
}


void Widget::setSize(unsigned int w, unsigned int h)
{
    width = w;
    height = h;
}

void Widget::setOrientation(int o)
{
    orientation = o;
}