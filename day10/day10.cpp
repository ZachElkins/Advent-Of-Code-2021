#include <iostream>
#include <fstream>
#include <vector>
#include "../helpers/BigInt.hpp"

int misMatches(std::vector<std::string> lines)
{
    std::string open = "";
    std::string errors = "";

    for (auto line : lines) {
        for (auto c : line) {
            if (c == ')')
            {
                if (open[open.size() - 1] == '(') { open = open.substr(0, open.size() - 1); }
                else { errors.push_back(c); break; }
            }
            else if (c == ']')
            {
                if(open[open.size() - 1] == '[') { open = open.substr(0, open.size() - 1); }
                else { errors.push_back(c); break; }
            }
            else if (c == '}')
            {
                if (open[open.size() - 1] == '{') { open = open.substr(0, open.size() - 1); }
                else { errors.push_back(c); break; }
            }
            else if (c == '>')
            {
                if (open[open.size() - 1] == '<') { open = open.substr(0, open.size() - 1); }
                else { errors.push_back(c); break; }
            } else {
                open.push_back(c);
            }
        }
    }

    int points = 0;

    for (auto e : errors) {
        switch (e) {
            case ')':
                points += 3;
                break;
            case ']':
                points += 57;
                break;
            case '}':
                points += 1197;
                break;
            case '>':
                points += 25137;
                break;
        }
    }

    return points;
}

BigInt finishLines(std::vector<std::string> lines)
{
    std::vector<BigInt> points;

    for (auto line : lines) {
        std::string open = "";
        bool corrupt = false;
        for (auto c : line) {
            if (c == ')')
            {
                if (open[open.size() - 1] == '(') { open = open.substr(0, open.size() - 1); }
                else { corrupt = true; break; }
            }
            else if (c == ']')
            {
                if(open[open.size() - 1] == '[') { open = open.substr(0, open.size() - 1); }
                else { corrupt = true; break; }
            }
            else if (c == '}')
            {
                if (open[open.size() - 1] == '{') { open = open.substr(0, open.size() - 1); }
                else { corrupt = true; break; }
            }
            else if (c == '>')
            {
                if (open[open.size() - 1] == '<') { open = open.substr(0, open.size() - 1); }
                else { corrupt = true; break; }
            } else {
                open.push_back(c);
            }

            int openSize = open.size();
            if (open[openSize-1] == ')' && open[openSize-2] == '(') { open = open.substr(0, openSize - 2); }
            if (open[openSize-1] == ']' && open[openSize-2] == '[') { open = open.substr(0, openSize - 2); }
            if (open[openSize-1] == '}' && open[openSize-2] == '[') { open = open.substr(0, openSize - 2); }
            if (open[openSize-1] == '>' && open[openSize-2] == '<') { open = open.substr(0, openSize - 2); }
        }

        if (!corrupt) {
            BigInt value = 0;
            for (int i = open.size(); i >= 0; i--) {
                char c = open[i];
                switch (c) {
                    case '(':
                        value = (5 * value) + 1;
                        break;
                    case '[':
                        value = (5 * value) + 2;
                        break;
                    case '{':
                        value = (5 * value) + 3;
                        break;
                    case '<':
                        value = (5 * value) + 4;
                        break;
                }
            }
            points.push_back(value);
        }
    }

    sort(points.begin(), points.end());
    
    return points[(int)(points.size()/2)];

    // return 0;
}

int main()
{
    // Setup
    std::ifstream file("input.txt");
    std::vector<std::string> lines;
    std::string line;

    while (file >> line)
    {
        lines.push_back(line);
    }

    // Part 1
    std::cout << "Part 1:\nThe corrupt lines are worth " << misMatches(lines) << " points." << std::endl;

    // Part 2
    std::cout << "Part 2:\nThe unfinished lines are worth " << finishLines(lines) << " points." << std::endl;

    return 0;
}