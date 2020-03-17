# Accelerator

This is simple project that use Genetic Algorithm to solve Traveling Salesman Problem (TSP). The visualization part is done with [SFML](https://www.sfml-dev.org/index.php) library.

The program will start with a set of solutions (randomly generated routes between cities) which is called `Population`. Solutions from one population are then taken and used to form a new population through `Selection`, `Cross-over` and `Mutation` methods. 

* `Selection`: The fittest solution of the `Population` is hand-picked to be included in the next generation.

* `Cross-over`: In each generation, there are chances that two solution can produce offspring, which contain genetic information from both parents.

* `Mutate`: After `cross-over`, each offspring can have a chance to mutate into totally new solution.

![](/result.JPG)

## Installation
### Windows
1. The project  uses [{fmt}](https://github.com/fmtlib/fmt/) library for formating output. The library can be easily installed with Microsoft's [vcpkg](https://github.com/Microsoft/vcpkg).
    * `vcpkg install fmt`
2. Clone the project: `git clone https://github.com/phuongtran7/Accelerator`.
3. Download and extract [SFML](https://www.sfml-dev.org/download.php) library. Adjust `include` and `lib` directory of the project.
4. Open project's `Property Pages` in Visual Studio. Select `Debugging`, adjust the `Enviroment` to point to the `bin` directory of SFML.
5. Build the project with Visual Studio.

## Usage
1. The dataset for TSP problem can be download here: [http://www.math.uwaterloo.ca/tsp/world/countries.html](http://www.math.uwaterloo.ca/tsp/world/countries.html).
2. Put the dataset (in `TSPLIB Format (.tsp)`) next to the executable. The program supports multiple `.tsp` files in the same location as the executable. It will ask to choose with dataset to use each startup.
3. Start the program.

## Notes
This project is extremely inefficient and incredibly slow. Don't run large dataset with high number of member and generation.

## Links

1. [Genetic Algorithm for Traveling Salesman Problem with Modified Cycle Crossover Operator](https://www.hindawi.com/journals/cin/2017/7430125/)
2. [Introduction to Genetic Algorithms — Including Example Code](https://towardsdatascience.com/introduction-to-genetic-algorithms-including-example-code-e396e98d8bf3)