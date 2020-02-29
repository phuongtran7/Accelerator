# Accelerator

This is simple project that use Genetic Algorithm to solve Traveling Salesman Problem (TSP).

The program will start with a set of solutions (randomly generated routes between cities) which is call `Population`. Solutions from one population are taken and used to form a new population through `Selection`, `Cross-over` and `Mutation` methods. 

* `Selection`: The fittest solution of the `Population` is hand-picked to be included in the next generation.

* `Cross-over`: In each generation, there are chances that two solution can produce offspring, which contain genetic information from both parents.

* `Mutate`: In each generation, each offspring can have a chance to mutate into totally new solution.

## Installation
### Windows
1. The project  uses [{fmt}](https://github.com/fmtlib/fmt/) library for formating output. The library can be easily installed with Microsoft's [vcpkg](https://github.com/Microsoft/vcpkg).
    * `vcpkg install fmt`
2. Clone the project: `git clone https://github.com/phuongtran7/Accelerator`.
3. Build the project with Visual Studio.

## Usage
1. The dataset for TSP problem can be download here: [www.math.uwaterloo.ca/tsp/world/countries.html](www.math.uwaterloo.ca/tsp/world/countries.html).
2. Put the dataset (in `TSPLIB Format`) next to the executable.
3. Start the program.

## Notes
This project is extremely inefficient and incredibly slow. Don't run large dataset with high number of member and generation.