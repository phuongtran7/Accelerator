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
	bool insert_city(City city, size_t index);
	bool replace_city(City city, size_t index);
	void add_city(City city);
	void randomize_trip();
	double get_fitness();
	bool swap_city(size_t first, size_t second);
	size_t get_trip_size();
	double get_total_distance();
};

