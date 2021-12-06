#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../helpers/BigInt.hpp"

int lanternFishSpawn(std::vector<int> &fish, int days)
{
    for (int d = 0; d < days; d++)
    {
        for (int f = fish.size()-1; f >= 0; f--)
        {
            if (fish[f] == 0)
            {
                fish[f] = 6;
                fish.push_back(8);
            }
            else
            {
                fish[f] = fish[f] - 1;
            }
        }
    }
    return fish.size();
}

BigInt lanternFishSpawnBigNumbers(BigInt fish [9], int days)
{
    for (int d = 0; d < days; d++)
    {
        BigInt to_reset = fish[0];
        for (int f = 0; f < 8; f++)
        {
            fish[f] = fish[f+1];
        }
        fish[6] = fish[6] + to_reset;
        fish[8] = to_reset;
    }

    BigInt total_fish = 0;
    for (int f = 0; f < 9; f++)
    {
        total_fish += fish[f];
    }

    return total_fish;
}


int main()
{
    // Setup
    std::ifstream file("input.txt");
    std::string line;
    std::vector<int> fish1;
    BigInt fish2 [] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    while(getline(file, line, ','))
    {
        int age = std::stoi(line);
        fish1.push_back(age);
        fish2[age] = fish2[age] + 1;
    }

    // Part 1
    int days = 80;
    std::cout << "Part 1: There will be "
        << lanternFishSpawn(fish1, days)
        << " Lantern Fish after "
        << days << " days."
        << std::endl;

    // Part 2
    days = 256;
    std::cout << "Part 2: There will be "
        << lanternFishSpawnBigNumbers(fish2, days)
        << " Lantern Fish after " 
        << days << " days."
        << std::endl;

    return 0;
}