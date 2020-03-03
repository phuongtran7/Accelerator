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
			}
			continue;
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
	auto fittest = population_.at(get_fittess().at(0));
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
	for (auto i = 0; i < population_size; i++) {
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

std::vector<size_t> Population::get_fittess()
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

	std::vector<size_t> return_vec{ fitness_table.at(fitness_table.size() - 1).first , fitness_table.at(fitness_table.size() - 2).first };
	return return_vec;
}

size_t Population::get_population_size()
{
	return population_.size();
}

void Population::start_next_generation()
{
	// First by selection. Get the fittest trip in this generation
	auto index = get_fittess();
	auto fittest_1 = population_.at(index.at(0));
	auto fittest_2 = population_.at(index.at(1));

	// Remove the trip from popution
	population_.erase(population_.begin() + index.at(0));
	population_.erase(population_.begin() + index.at(1));

	std::vector<Trip> new_gen = { fittest_1, fittest_2 };

	// Cross over the rest
	cross_over();

	for (auto trip : population_) {
		new_gen.push_back(trip);
	}
	population_.clear();
	population_ = new_gen;
}

void Population::mutate(Trip& trip) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> double_dis(0.0, 1.0);

	// Determine whether trip should mutate
	auto chance = double_dis(gen);
	if (chance > 0.5) {
		std::uniform_int_distribution<> int_dist(0, trip.get_trip_size() - 1);
		trip.swap_city(int_dist(gen), int_dist(gen));
	}
}

void Population::cross_over()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	for (auto index = 0; index < population_.size(); index += 2) {

		std::uniform_int_distribution<> index_dist(0, population_.at(index).get_trip_size() - 1);
		auto cross_over_index_1 = index_dist(gen);
		int cross_over_index_2{};
		do {
			cross_over_index_2 = index_dist(gen);
		} while (cross_over_index_2 == cross_over_index_1);

		// Swap the index if the cross_over_index_1 is larger
		if (cross_over_index_1 > cross_over_index_2) {
			auto temp = cross_over_index_1;
			cross_over_index_1 = cross_over_index_2;
			cross_over_index_2 = temp;
		}

		Trip child_1{};
		Trip child_2{};

		for (auto i = 0; i < population_.at(index).get_trip_size(); i++) {
			// Fill the children with empty city and swap the crossover section from parents
			if (i >= cross_over_index_1 && i <= cross_over_index_2) {
				child_2.add_city(population_.at(index).get_city(i).value());
				child_1.add_city(population_.at(index + 1).get_city(i).value());
			}
			else {
				child_2.add_city(City{ 0,0,0 });
				child_1.add_city(City{ 0,0,0 });
			}
		}

		for (auto i = 0; i < population_.at(index).get_trip_size(); i++) {
			//Iterate over parent 1 to fill up empty spot in child 2

			auto city = population_.at(index).get_city(i).value();

			bool conflicted = false;
			for (auto j = cross_over_index_1; j <= cross_over_index_2; j++) {
				if (city.get_id() == child_2.get_city(j).value().get_id()) {
					conflicted = true;
					break;
				}
			}

			if (!conflicted) {
				// If there is no conflicted with the swapped section from parent 2
				// Replace the empty city with city from parent 1
				child_2.replace_city(city, i);
			}
		}


		for (auto i = 0; i < population_.at(index + 1).get_trip_size(); i++) {
			//Iterate over parent 1 to fill up empty spot in child 2

			auto city = population_.at(index + 1).get_city(i).value();

			bool conflicted = false;
			for (auto j = cross_over_index_1; j <= cross_over_index_2; j++) {
				if (city.get_id() == child_1.get_city(j).value().get_id()) {
					conflicted = true;
					break;
				}
			}

			if (!conflicted) {
				// If there is no conflicted with the swapped section from parent 1
				// Replace the empty city with city from parent 2
				child_1.replace_city(city, i);
			}
		}

		// Finally replace the parent with children
		for (auto i = 0; i < population_.at(index).get_trip_size(); i++) {
			population_.at(index).replace_city(child_2.get_city(i).value(), i);
			population_.at(index + 1).replace_city(child_1.get_city(i).value(), i);
		}

		// Mutate the new offspring
		mutate(population_.at(index));
		mutate(population_.at(index + 1));
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
