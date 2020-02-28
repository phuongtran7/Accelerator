#include "City.h"

City::City(size_t id, double x, double y) :
	id_{id},
	x_{x},
	y_{y}
{
}

double City::get_x()
{
	return x_;
}

double City::get_y()
{
	return y_;
}

size_t City::get_id()
{
	return id_;
}

double City::distance_to(const City& another)
{
	return std::sqrt((std::pow((another.x_ - x_), 2)) + (std::pow((another.y_ - y_), 2)));
}
