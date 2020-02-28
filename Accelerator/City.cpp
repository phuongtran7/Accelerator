#include "City.h"

City::City() : City(0, 0, 0)
{
}

City::City(unsigned int id, double x, double y) :
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

unsigned int City::get_id()
{
	return id_;
}

double City::distance_to(const City& another)
{
	return std::sqrt((std::pow((another.x_ - x_), 2)) + (std::pow((another.y_ - y_), 2)));
}
