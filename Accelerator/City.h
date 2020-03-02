#pragma once
#include <cmath>

// Represent each city in the tour
class City
{
private:
	size_t id_;
	double x_;
	double y_;
public:
	City() = delete;
	City(size_t id, double x, double y);
	~City() = default;
	double get_x();
	double get_y();
	size_t get_id();
	double distance_to(const City& another);
};