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

bool Trip::insert_city(City city, size_t index)
{
	if (index > trip_.size()) {
		return false;
	}

	trip_.insert(trip_.begin() + index, city);
	return true;
}

bool Trip::replace_city(City city, size_t index)
{
	if (index > trip_.size()) {
		return false;
	}

	trip_.at(index) = city;
	return true;
}

void Trip::add_city(City city)
{
	trip_.push_back(city);
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
		auto t = 1.0 / total_distance;
		return (t);
	}
	return 0.0;
}

bool Trip::swap_city(size_t first, size_t second)
{
	if (first >= trip_.size() || second >= trip_.size()) {
		return false;
	}
	std::swap(trip_.at(first), trip_.at(second));
	return true;
}

size_t Trip::get_trip_size()
{
	return trip_.size();
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

std::pair<double, double> Trip::get_x_range() {
	std::sort(trip_.begin(), trip_.end(),
		[](auto& a, auto& b) -> bool
		{
			return a.get_x() < b.get_x();
		});

	auto range = std::make_pair(trip_.at(0).get_x(), trip_.at(trip_.size() - 1).get_x());
	round_range(range);
	return range;
}

std::pair<double, double> Trip::get_y_range() {
	std::sort(trip_.begin(), trip_.end(),
		[](auto& a, auto& b) -> bool
		{
			return a.get_y() < b.get_y();
		});

	auto range = std::make_pair(trip_.at(0).get_y(), trip_.at(trip_.size() - 1).get_y());
	round_range(range);
	return range;
}