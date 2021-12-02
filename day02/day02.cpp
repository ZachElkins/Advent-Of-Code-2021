#include <iostream>
#include <fstream>
#include <vector>

struct Position
{
    int horizontal;
    int depth;
    int aim;
};

struct Command
{
    std::string operation;
    int value;
};

Position finalPosition(std::vector<Command> commands)
{
    Position pos;
    pos.horizontal = 0;
    pos.depth = 0;

    for (int i = 0; i < commands.size(); i++)
    {
        if (commands[i].operation == "forward") 
        {
            pos.horizontal += commands[i].value;
        }
        else
        {
            if (commands[i].operation == "down") { pos.depth += commands[i].value; }
            else if (commands[i].operation == "up") { pos.depth -= commands[i].value; }
        }
    }

    return pos; 
}

Position finalPositionAim(std::vector<Command> commands)
{
    Position pos;
    pos.horizontal = 0;
    pos.depth = 0;
    pos.aim = 0;

    for (int i = 0; i < commands.size(); i++)
    {
        if (commands[i].operation == "forward")
        {
            pos.horizontal += commands[i].value;
            pos.depth += commands[i].value*pos.aim;
        }
        else
        {
            if (commands[i].operation == "down") { pos.aim += commands[i].value; }
            else if (commands[i].operation == "up") { pos.aim -= commands[i].value; }
        }
    }

    return pos;
}

int main()
{

    // Setup
    std::ifstream file("input.txt");
    std::string line;
    std::vector<Command> commands;

    while (std::getline(file, line))
    {
        Command cmd;
        int pos = line.find(" ");
        cmd.operation = line.substr(0, pos);
        cmd.value = std::stoi(line.substr(pos + 1));
        commands.push_back(cmd);
    }

    // Part 1
    Position pos1 = finalPosition(commands);
    std::cout << "Part 1: The final horiztonal position is " 
        << pos1.horizontal 
        << " and the final depth is "
        << pos1.depth
        << ".\n\tSo the solution is "
        << pos1.horizontal*pos1.depth << std::endl;

    // Part 2
    Position pos2 = finalPositionAim(commands);
    std::cout << "Part 2: The final horiztonal position is " 
        << pos2.horizontal << " the final depth is "
        << pos2.depth << " and the final aim is " 
        << pos2.aim << ".\n\tSo the solution is "
        << pos2.horizontal*pos2.depth << std::endl;

    return 0;
}