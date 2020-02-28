#pragma once
#include "Trip.h"
#include <vector>
#include <optional>

// Represent a generation of trips
class Population
{
private:
	std::vector<Trip> population_;
	
public:
	Population();
	Population(size_t population_size);
	~Population() = default;
	std::optional<Trip> get_trip(size_t index);
	bool set_trip(Trip& trip, size_t index);
	Trip get_fittess();
};

