#include <iostream>
#include "fmt/format.h"
#include "Population.h"
#include <chrono>

int main()
{
	Population Nora("dj38.tsp", 100);
	auto t1 = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < 10000; i++) {
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
