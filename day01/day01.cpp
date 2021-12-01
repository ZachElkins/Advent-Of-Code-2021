#include "day01.h"

int main()
{
    // Setup
    std::ifstream file("input.txt");
    std::string input;
    std::vector<int> values;

    while (file >> input) values.push_back(std::stoi(input));

    // Part 1
    int numIncreasing = numIncreasingValues(values);
    std::cout << "Part 1: There are " << numIncreasing << " inceasing values" << std::endl;

    // Part 2
    int numWindowIncreasing = numIncreasingWindow(values, 3);
    std::cout << "Part 2: There are " << numWindowIncreasing << " inceasing values in a window of 3" << std::endl;

    return 0;
}

int numIncreasingValues(std::vector<int> values)
{
    int numIncreasing = 0;
    int last = values[0];

    for (int i = 1; i < values.size(); i++) {
        if (values[i] > last) numIncreasing++;
        
        last = values[i];
    }

    return numIncreasing;
}

int numIncreasingWindow(std::vector<int> values, int window)
{
    int numIncreasing = 0;
    int lastWindow = 0;
    
    for (int i = 0; i < window; i++) lastWindow += values[i];
    
    for (int i = 1; i < values.size()-window+1; i++) {
        int currentWindow = 0;

        for (int w = 0; w < window; w++) currentWindow += values[i+w];

        if (currentWindow > lastWindow) numIncreasing++;

        lastWindow = currentWindow;
    }

    return numIncreasing;
}