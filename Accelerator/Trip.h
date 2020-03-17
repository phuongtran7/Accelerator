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

private:
	// Round down the starting point and round up the ending point
	template <typename Type>
	void round_range(std::pair<Type, Type>& input) {
		auto first = input.first;
		auto second = input.second;

		input.first = ((first - 99) / 100) * 100;
		input.second = ((second + 99) / 100) * 100;
	}

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
	std::pair<double, double> get_x_range();
	std::pair<double, double> get_y_range();
};

