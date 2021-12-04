#include <iostream>
#include <fstream>
#include <vector>

struct Power {
    uint32_t gamma;
    uint32_t epsilon;
};

Power powerRates(std::vector<std::string> data)
{
    std::string mostCommon = "";

    // Loop through each character in the binary data
    for (int i = 0; i < data[0].size(); i++)
    {
        int ones = 0;
        // Loop through each string and look at a distinct letter
        for (int j = 0; j < data.size(); j++)
        {
            if (data[j][i] == '1') { ones++; }
        }
        mostCommon = ones > data.size() / 2 ? mostCommon + "1" : mostCommon + "0";
    }

    Power power;

    power.gamma = stoi(mostCommon, 0, 2);
    
    // flip most common bits to least common bits
    for (int i = 0; i < mostCommon.size(); i++) { mostCommon[i] = mostCommon[i] == '1' ? '0' : '1'; }
    power.epsilon = stoi(mostCommon, 0, 2);

    return power;
}


struct LifeSupport {
    uint32_t oxygen;
    uint32_t c02;
};

LifeSupport lifeSupportRates(std::vector<std::string> data)
{
    LifeSupport lifeSupport;

    // Oxygen
    std::string mostCommon = "";
    std::vector<std::string> leftOver = data;

    // Loop through each character in the binary data
    for (int i = 0; i < data[0].size(); i++)
    {
        int ones = 0;
        // Loop through each string and look at a distinct letter
        for (int j = 0; j < leftOver.size(); j++)
        {
            if (leftOver[j][i] == '1') { ones++; }
        }
        mostCommon = ones >= leftOver.size()-ones ? mostCommon + "1" : mostCommon + "0";

        std::vector<std::string> temp = leftOver;
        leftOver.erase(leftOver.begin(), leftOver.end());
        // Add all the values that match the mostCommon ones to the leftOver vector
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j].substr(0, mostCommon.size()) == mostCommon) 
            {
                leftOver.push_back(temp[j]);
            }
        }

        if (leftOver.size() == 1) { break; }
    }
    lifeSupport.oxygen = stoi(leftOver[0], 0, 2);

    // CO2
    std::string leastCommon = "";
    leftOver = data;
    // Loop through each character in the binary data
    for (int i = 0; i < data[0].size(); i++)
    {
        int ones = 0;
        // Loop through each string and look at a distinct letter
        for (int j = 0; j < leftOver.size(); j++)
        {
            if (leftOver[j][i] == '1') { ones++; }
        }
        leastCommon = ones < leftOver.size()-ones ? leastCommon + "1" : leastCommon + "0";

        std::vector<std::string> temp = leftOver;
        leftOver.erase(leftOver.begin(), leftOver.end());
        // Add all the values that match the mostCommon ones to the leftOver vector
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j].substr(0, leastCommon.size()) == leastCommon) 
            {
                leftOver.push_back(temp[j]);
            }
        }

        if (leftOver.size() == 1) { break; }
    }

    lifeSupport.c02 = stoi(leftOver[0], 0, 2);

    return lifeSupport;
}

int main() {

    // Setup
    std::ifstream file("input.txt");
    std::vector<std::string> data;
    std::string line;

    while(file >> line) { data.push_back(line); }

    // Part 1
    Power power = powerRates(data);
    std::cout << "Part 1: Gamme Rate = " << power.gamma
        << " Epsilon Rate = " <<  power.epsilon
        << ".\n\tSolution: " << power.gamma* power.epsilon << std::endl;

    // Part 2
    LifeSupport lifeSupport = lifeSupportRates(data);
    std::cout << "Part 2: Oxygen Rate = " << lifeSupport.oxygen
        << " CO2 Rate = " <<  lifeSupport.c02
        << ".\n\tSolution: " << lifeSupport.oxygen * lifeSupport.c02 << std::endl;
    
    return 0;
}