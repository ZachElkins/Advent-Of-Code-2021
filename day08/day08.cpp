#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

struct Signal
{
    std::vector<std::string> pattern;
    std::vector<std::string> output;
};

bool setEquals(std::set<char> a, std::set<char> b)
{
    if (a.size() != b.size())
        return false;

    for (auto c : a)
    {
        if (b.find(c) == b.end())
            return false;
    }

    return true;
}

std::set<char> setDifference(std::set<char> a, std::set<char> b)
{
    std::set<char> c;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
    return c;
}

std::set<char> setIntersection(std::set<char> a, std::set<char> b)
{
    std::set<char> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<char> multiSetIntersection(std::vector< std::set<char> > sets)
{
    std::set<char> s = sets[0];
    for (int i = 1; i != sets.size(); ++i) { s = setIntersection(s, sets[i]); }
    return s;
}

std::vector<std::string> explode(std::string str, char delimiter)
{
    std::vector<std::string> output;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter)) {
        if (token.size() > 0) {
            output.push_back(token);
        }
    }

    return output;
}

int uniqueLengthDigits (std::vector<Signal> signals)
{
    // Unique Length Digits represent 1  4  7  8 in a seven segment display
    std::vector<int> uniqueLengths = {2, 4, 3, 7};
    int uniqueLengthDigits = 0;

    for (int i = 0; i < signals.size(); i++) {
        for (int j = 0; j < signals[i].output.size(); j++)
        {
            if (std::count(uniqueLengths.begin(), uniqueLengths.end(), signals[i].output[j].size()))
            {
                uniqueLengthDigits++;
            }
        }
    }

    return uniqueLengthDigits;
}

std::set<char> findKnownValue(std::vector<std::string> input, int len)
{
    std::set<char> s;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].size() == len)
        {
            for (char c: input[i])
            {
                s.insert(c);
            }
            return s;
        }
    }

    return s;
}

std::vector< std::set<char> > findUnknownValue(std::vector<std::string> input, int len)
{
    std::vector< std::set<char> > uk;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].size() == len)
        {
            std::set<char> s;
            for (char c: input[i])
            {
                s.insert(c);
            }
            uk.push_back(s);
        }
    }

    return uk;
}

std::vector<char> decode(Signal signal)
{
    std::vector<std::string> values;
    for (int i = 0; i < signal.pattern.size(); i++) { values.push_back(signal.pattern[i]); }
    for (int i = 0; i < signal.output.size(); i++) { values.push_back(signal.output[i]); }

    std::set<char> known_1 = findKnownValue(values, 2);
    std::set<char> known_4 = findKnownValue(values, 4);
    std::set<char> known_7 = findKnownValue(values, 3);
    std::set<char> known_8 = findKnownValue(values, 7);
    std::vector< std::set<char> > uk_235 = findUnknownValue(values, 5);
    std::vector< std::set<char> > uk_069 = findUnknownValue(values, 6);
    std::set<char> intersect_235 = multiSetIntersection(uk_235);
    std::set<char> intersect_069 = multiSetIntersection(uk_069);
    
    //
    //  Segments:
    //     0 0 
    //   5     1
    //   5     1
    //     6 6 
    //   4     2
    //   4     2
    //     3 3 
    //

    std::set<char> s0 = setDifference(known_7, known_1);
    std::set<char> s3 = setDifference(setDifference(intersect_235, known_4), known_7);
    std::set<char> s6 = setIntersection(intersect_235, known_4);
    std::set<char> s2 = setIntersection(intersect_069, known_1);
    std::set<char> s1 = setDifference(setDifference(known_7, s2), s0);
    std::set<char> s5 = setDifference(setDifference(setDifference(known_4, s6), s1), s2);
    std::set<char> s4 = setDifference(setDifference(setDifference(known_8, known_4), s0), s3);

    return {*s0.begin(), *s1.begin(), *s2.begin(), *s3.begin(), *s4.begin(), *s5.begin(), *s6.begin()};
}

// valueOfSegments
std::vector< std::set<char> > valueOfSegments(std::vector<char> segments)
{
    std::vector< std::set<char> > values;
    std::set<char> v0 = {segments[0], segments[1], segments[2], segments[3], segments[4], segments[5]};
    std::set<char> v1 = {segments[1], segments[2]};
    std::set<char> v2 = {segments[0], segments[1], segments[3], segments[4], segments[6]};
    std::set<char> v3 = {segments[0], segments[1], segments[2], segments[3], segments[6]};
    std::set<char> v4 = {segments[1], segments[2], segments[5], segments[6]};
    std::set<char> v5 = {segments[0], segments[2], segments[3], segments[5], segments[6]};
    std::set<char> v6 = {segments[0], segments[2], segments[3], segments[4], segments[5], segments[6]};
    std::set<char> v7 = {segments[0], segments[1], segments[2]};
    std::set<char> v8 = {segments[0], segments[1], segments[2], segments[3], segments[4], segments[5], segments[6]};
    std::set<char> v9 = {segments[0], segments[1], segments[2], segments[3], segments[5], segments[6]};

    return {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9};
}

std::vector<int> findOutputValues(std::vector<Signal> signals)
{
    std::vector<int> convertedValues;
    for (int i = 0; i < signals.size(); i++)
    // for (int i = 0; i < 3; i++)
    {
        std::vector<char> segments = decode(signals[i]);
        std::vector< std::set<char> > numbers = valueOfSegments(segments);
        std::string value = "";
        for (int j = 0; j < signals[i].output.size(); j++)
        {
            std::string outputString = signals[i].output[j];
            std::set<char> outputSet;
            // std::cout << "OUTSTRING " << outputString << std::endl;
            for (char c: outputString)
            {
                outputSet.insert(c);
            }

            for (int k = 0; k < numbers.size(); k++)
            {
                if (setEquals(numbers[k], outputSet))
                {
                    value += std::to_string(k);
                }
            }
        }
        convertedValues.push_back(std::stoi(value));
    }

    return convertedValues;
}

int main()
{
    // Setup
    std::ifstream file("input.txt");
    std::string line;
    std::vector<Signal> signals;
    bool firstPartition = true;

    while (std::getline(file, line))
    {
        Signal currentSignal;
        std::vector<std::string> partition = explode(line, ' ');
        for (int i = 0; i < partition.size(); i++)
        {
            if (partition[i] == "|")
            {
                firstPartition = false;
                continue;
            }
            else if (firstPartition)
            {
                currentSignal.pattern.push_back(partition[i]);
            }
            else
            {
                currentSignal.output.push_back(partition[i]);
            }
        }

        firstPartition = true;

        signals.push_back(currentSignal);
    }
    
    // Part 1
    std::cout << "Part 1:\nThere are " << uniqueLengthDigits(signals) << " digits with a unique length in the outputs." << std::endl;

    // Part 2
    std::vector<int> outputValues = findOutputValues(signals);
    int finalValue = 0;
    for (int i = 0; i < outputValues.size(); i++) { finalValue += outputValues[i]; }
    std::cout << "Part 2:\nThe sum of the ouputs is " << finalValue << "." << std::endl;

    return 0;
}