#include <iostream>
#include "fmt/format.h"
#include "Population.h"
#include <chrono>
#include <filesystem>

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

	Population Nora(file_name, pop_size);
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

	std::getchar();
}
