#pragma once
#include <cmath>

// Represent each city in the tour
class City
{
private:
	unsigned int id_;
	double x_;
	double y_;
public:
	City();
	City(unsigned int id, double x, double y);
	~City() = default;
	double get_x();
	double get_y();
	unsigned int get_id();
	double distance_to(const City& another);
};

