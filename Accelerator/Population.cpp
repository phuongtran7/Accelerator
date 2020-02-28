#include "Population.h"

Population::Population() :
	Population(50) // Default to 50 member in a population
{
}

Population::Population(size_t population_size) :
	population_{}
{
	population_.reserve(50);
}

std::optional<Trip> Population::get_trip(size_t index)
{
	if (index > population_.size()) {
		return std::nullopt;
	}
	return population_.at(index);
}

bool Population::set_trip(Trip& trip, size_t index)
{
	if (index > population_.size()) {
		return false;
	}

	population_.insert(population_.begin() + index, trip);
	return true;
}

Trip Population::get_fittess()
{
	auto current_fittest = 0.0;
	auto fittest_index = -1;
	for (auto index = 0; index < population_.size(); index++) {
		auto fitness = population_.at(index).get_fitness();
		if (fitness > current_fittest) {
			current_fittest = fitness;
			fittest_index = index;
		}
	}
	return population_.at(fittest_index);
}
