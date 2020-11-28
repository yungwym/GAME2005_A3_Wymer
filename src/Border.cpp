#include "Border.h"


Border::Border(glm::vec2 pos, int width, int height)
{
	getTransform()->position = pos;
	setWidth(width);
	setHeight(height);

}

Border::~Border()
= default;

void Border::draw()
{

}

void Border::update()
{

}

void Border::clean()
{

}

