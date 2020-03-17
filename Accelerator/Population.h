#pragma once
#include "Trip.h"
#include <vector>
#include <optional>
#include <sstream>
#include <fstream>
#include "fmt/format.h"
#include <string>
#include <agents.h>

// Represent a generation of trips
class Population
{
private:
	std::vector<Trip> population_;
	concurrency::ITarget<Trip>& target_;
	std::pair<double, double> x_range_;
	std::pair<double, double> y_range_;

public:
	Population(const std::string& filename, concurrency::ITarget<Trip>& target);
	Population(const std::string& filename, size_t population_size, concurrency::ITarget<Trip>& target);
	~Population() = default;
	std::optional<Trip> get_trip(size_t index);
	bool set_trip(Trip& trip, size_t index);
	void add_trip(Trip& trip);
	void start_next_generation();
	void report_data();
	std::pair<double, double> get_x_range();
	std::pair<double, double> get_y_range();

private:
	void mutate(Trip& city);
	void cross_over();
	std::vector<std::string> split_string(const std::string& input);
	Trip get_initial_data(const std::string& filename);
	std::vector<size_t> get_fittess();
	size_t get_population_size();
};
