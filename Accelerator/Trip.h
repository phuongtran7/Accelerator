#pragma once
#include "City.h"
#include <vector>
#include <optional>
#include <algorithm>
#include <random>

// Represent the trip around all the cities and back
class Trip
{
private:
	std::vector<City> trip_;

public:
	Trip();
	~Trip() = default;
	std::optional<City> get_city(size_t index);
	bool insert_city(City& city, size_t index);
	void randomize_trip();
	double get_fitness();

private:
	double get_total_distance();
};

