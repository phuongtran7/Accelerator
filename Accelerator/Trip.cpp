#include "Trip.h"

Trip::Trip() :
	trip_{}
{
}

std::optional<City> Trip::get_city(size_t index)
{
	if (index > trip_.size()) {
		return std::nullopt;
	}
	return trip_.at(index);
}

bool Trip::insert_city(City& city, size_t index)
{
	if (index > trip_.size()) {
		return false;
	}

	trip_.insert(trip_.begin() + index, city);
}

void Trip::randomize_trip()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(trip_.begin(), trip_.end(), g);
}

double Trip::get_fitness()
{
	auto total_distance = get_total_distance();
	if (total_distance != 0.0) {
		return (1.0 / total_distance);
	}
	return 0.0;
}

double Trip::get_total_distance()
{
	if (trip_.size() != 0) {
		double distance{};
		for (size_t index = 0; index < trip_.size(); index++) {
			if (index != (trip_.size() - 1)) {
				distance += trip_.at(index).distance_to(trip_.at(index + 1));
			}
		}
		return distance;
	}
	return 0.0;
}
