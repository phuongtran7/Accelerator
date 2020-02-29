#include "Population.h"

Trip Population::get_initial_data(const std::string& filename)
{
	Trip new_trip{};
	std::ifstream infile(filename);
	std::string line;
	bool found_node_section{ false };
	while (std::getline(infile, line))
	{
		if (!found_node_section) {
			if (line == "NODE_COORD_SECTION") {
				found_node_section = true;
				continue;
			}
			else {
				continue;
			}
		}

		auto tokens = split_string(line);
		if (tokens.size() == 3) {
			City city{ std::stoul(tokens.at(0)), std::stod(tokens.at(1)), std::stod(tokens.at(2)) };
			new_trip.add_city(city);
		}
	}
	return new_trip;
}

void Population::report_data()
{
	auto fittest = population_.at(get_fittess());
	fmt::print("Current fittest trip\n");
	for (auto i = 0; i < fittest.get_trip_size(); i++) {
		fmt::print("{} ", fittest.get_city(i).value().get_id());
	}
	fmt::print("\nTrip lenght: {}", fittest.get_total_distance());
	fmt::print("\n\n");
}

Population::Population(const std::string& filename) :
	Population(filename, 50) // Default to 50 member in a population
{
}

Population::Population(const std::string& filename, size_t population_size) :
	population_{}
{
	population_.reserve(population_size);
	auto zero_dawn = get_initial_data(filename);
	for (auto i = 0; i < (population_size - 1); i++) {
		zero_dawn.randomize_trip();
		population_.push_back(zero_dawn);
	}
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

void Population::add_trip(Trip& trip)
{
	population_.push_back(trip);
}

size_t Population::get_fittess()
{
	std::vector<std::pair<size_t, double>> fitness_table;

	for (auto index = 0; index < population_.size(); index++)
	{
		auto fitness = population_.at(index).get_fitness();
		fitness_table.push_back(std::make_pair(index, fitness));
	}

	std::sort(fitness_table.begin(), fitness_table.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	return fitness_table.at(fitness_table.size() - 1).first;
}

size_t Population::get_population_size()
{
	return population_.size();
}

void Population::start_next_generation()
{
	// First by selection. Get the fittest trip in this generation
	auto index = get_fittess();
	auto fittest = population_.at(index);
	// Remove the trip from popution
	population_.erase(population_.begin() + index);
	std::vector<Trip> new_gen = { fittest };

	// Cross over the rest
	cross_over();

	// Mutate the cross over children
	mutate();

	for (auto trip : population_) {
		new_gen.push_back(trip);
	}
	population_.clear();
	population_ = new_gen;
}

void Population::mutate() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> double_dis(0.0, 1.0);

	for (auto& trip : population_) {
		// Determine whether each trip should mutate
		auto chance = double_dis(gen);
		if (chance > 0.5) {
			std::uniform_int_distribution<> int_dist(0, population_.size() - 1);
			trip.swap_city(int_dist(gen), int_dist(gen));
		}
	}
}

void Population::cross_over()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> num_dist(0, population_.size() - 1);
	// Randomly pick number of trip pair to do cross over
	auto number_of_pair = num_dist(gen);

	for (auto index = 0; index <= number_of_pair; index += 2) {
		// Randomly pick the pairs

		auto parent_1 = num_dist(gen);
		auto parent_2 = num_dist(gen);

		std::uniform_int_distribution<> index_dist(0, population_.at(parent_1).get_trip_size() - 1);
		auto cross_over_index = index_dist(gen);

		for (auto i = 0; i < cross_over_index; i++) {
			auto c1 = population_.at(parent_1).get_city(i).value();
			auto c2 = population_.at(parent_2).get_city(i).value();
			population_.at(parent_1).replace_city(c2, i);
			population_.at(parent_2).replace_city(c1, i);
		}
	}

}

std::vector<std::string> Population::split_string(const std::string& input)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(input);
	while (std::getline(tokenStream, token, ' '))
	{
		tokens.push_back(token);
	}
	return tokens;
}
