#include <iostream>
#include "fmt/format.h"
#include "Population.h"

int main()
{
	Population Nora("dj38.tsp", 1000);

	for (auto i = 0; i < 1000; i++) {
		Nora.report_data();
		Nora.start_next_generation();
	}

	std::getchar();
}
