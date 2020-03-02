#pragma once
#include "Trip.h"
#include <vector>
#include <optional>
#include <sstream>
#include <fstream>
#include "fmt/format.h"
#include <string>

// Represent a generation of trips
class Population
{
private:
	std::vector<Trip> population_;
	
public:
	Population(const std::string& filename);
	Population(const std::string& filename, size_t population_size);
	~Population() = default;
	std::optional<Trip> get_trip(size_t index);
	bool set_trip(Trip& trip, size_t index);
	void add_trip(Trip& trip);
	void start_next_generation();
	void report_data();
private:
	void mutate(Trip& city);
	void cross_over();
	std::vector<std::string> split_string(const std::string& input);
	Trip get_initial_data(const std::string& filename);
	std::vector<size_t> get_fittess();
	size_t get_population_size();
};
