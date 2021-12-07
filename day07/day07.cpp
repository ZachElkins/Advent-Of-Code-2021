#include <iostream>
#include <fstream>
#include <vector>

int minFuelAlign(std::vector<int> positions) {
    int min = *min_element(positions.begin(), positions.end());
    int max = *max_element(positions.begin(), positions.end());

    int minFuel = INT_MAX;

    for (int i = min; i <= max; i++) {
        int totalFuelUsed = 0;
        for (int p = 0; p < positions.size(); p++) {
            // x_i = abs(p-i)
            // f(x_i) = x_i
            totalFuelUsed = totalFuelUsed + std::abs(positions[p]-i);
        }
        if (totalFuelUsed < minFuel) {
            minFuel = totalFuelUsed;
        }
    }

    return minFuel;
}

int minFuelAlignCrabStyle(std::vector<int> positions) {
    int min = *min_element(positions.begin(), positions.end());
    int max = *max_element(positions.begin(), positions.end());

    int minFuel = INT_MAX;

    for (int i = min; i <= max; i++) {
        int totalFuelUsed = 0;
        for (int p = 0; p < positions.size(); p++) {
            // x = abs(p-i)
            // f(x_i) = (x_i*x_(i+1))/2
            int distance = std::abs(positions[p]-i);
            totalFuelUsed = totalFuelUsed + (distance*(distance+1))/2;
        }
        if (totalFuelUsed < minFuel) {
            minFuel = totalFuelUsed;
        }
    }

    return minFuel;
}


int main() {

    // Setup
    std::ifstream file("input.txt");
    std::string line;
    std::vector<int> positions;

    while (getline(file, line, ',')) 
    {
        positions.push_back(std::stoi(line));
    }

    // Part 1
    std::cout << "Part 1:\nThe minimum fuel required to align all the crabs is " << minFuelAlign(positions) << "." << std::endl;
    // Part 2
    std::cout << "Part 2:\nThe actual minimum fuel required to align all the crabs is " << minFuelAlignCrabStyle(positions) << "." << std::endl;

    return 0;
}