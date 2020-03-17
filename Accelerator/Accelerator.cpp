#include <iostream>
#include "fmt/format.h"
#include "Population.h"
#include <chrono>
#include <filesystem>
#include <agents.h>
#include <thread>
#include <SFML/Graphics.hpp>

std::string get_input() {
	std::vector<std::string> files{};
	auto current_path = std::filesystem::current_path();
	for (const auto& entry : std::filesystem::directory_iterator(current_path)) {
		// Look for ".tsp" file in the directory
		auto ext = entry.path().extension().generic_string();
		if (ext == ".tsp") {
			files.push_back(entry.path().filename().string());
		}
	}

	if (!files.empty()) {
		if (files.size() > 1) {
			fmt::print("There are multiple \".tsp\" files. Please choose one: \n");
			for (auto i = 0; i < files.size(); i++) {
				fmt::print("{} - {}\n", i, files.at(i));
			}

			int choice;
			std::cin >> choice;
			std::cin.get();
			return files.at(choice);
		}
		else {
			return files.at(0);
		}
	}
	else {
		fmt::print("Cannot find \".tsp\" files. Shutting down.\n");
		return "";
	}
}

template <typename Input, typename RangeA, typename RangeB>
auto map_value(Input input, RangeA beginA, RangeA endA, RangeB beginB, RangeB endB) {
	// If your number X falls between A and B, and you would like Y to fall between C and D, you can apply the following linear transform:
	// Y = (X-A)/(B-A) * (D-C) + C
	return ((input - beginA) / (endA - beginA)) * ((endB - beginB) + beginB);
}

int main()
{
	auto file_name = get_input();
	if (file_name.empty()) {
		return 1;
	}

	size_t pop_size, gen_size;
	fmt::print("Please specify how large the population: ");
	std::cin >> pop_size;
	std::cin.get();
	fmt::print("Please specify how many generation: ");
	std::cin >> gen_size;
	std::cin.get();

	concurrency::overwrite_buffer<Trip> buffer;

	Population Nora(file_name, pop_size, buffer);

	auto x_range = Nora.get_x_range();
	auto y_range = Nora.get_y_range();


	std::thread calculation_thread([&] {
		auto t1 = std::chrono::high_resolution_clock::now();
		for (auto i = 0; i < gen_size; i++) {
			Nora.report_data();
			Nora.start_next_generation();
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = (t2 - t1);

		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
		duration -= minutes;
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);

		fmt::print("Complete in {} minutes {} seconds.\n", minutes.count(), seconds.count());
		}
	);


	sf::RenderWindow window(sf::VideoMode(550, 550), "Abathur");

	sf::RectangleShape horizontal(sf::Vector2f(515, 5.f));
	sf::RectangleShape vertical(sf::Vector2f(515, 5.f));
	vertical.rotate(90);

	horizontal.setPosition(0, 515);
	vertical.setPosition(10, 10);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		window.draw(horizontal);
		window.draw(vertical);

		Trip fittest_trip;
		auto result = concurrency::try_receive(buffer, fittest_trip);

		if (result) {
			auto trip_size = fittest_trip.get_trip_size();
			for (auto i = 0; i < trip_size; i++) {

				auto current_city = fittest_trip.get_city(i).value();

				auto mapped_X = map_value(current_city.get_x(), x_range.first, x_range.second, 5.0, 500.0);
				auto mapped_Y = map_value(current_city.get_y(), y_range.first, y_range.second, 10.0, 500.0);

				sf::CircleShape shape(3);
				shape.setOrigin(shape.getRadius(), shape.getRadius());
				shape.setFillColor(sf::Color::Green);
				shape.setPosition(mapped_X, mapped_Y);

				window.draw(shape);

				if (i < (trip_size - 1)) {
					auto next_city = fittest_trip.get_city(i+1).value();

					sf::Vertex line[] =
					{
						sf::Vertex(sf::Vector2f(mapped_X, mapped_Y)),
						sf::Vertex(sf::Vector2f(map_value(next_city.get_x(), x_range.first, x_range.second, 5.0, 500.0),
												map_value(next_city.get_y(), y_range.first, y_range.second, 10.0, 500.0))),
					};

					window.draw(line, 2, sf::Lines);
				}
			}

			window.display();
		}
	}

	calculation_thread.join();
	return 0;
}
