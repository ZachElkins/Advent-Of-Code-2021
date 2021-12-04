#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<uint32_t> explode(std::string str, char delimiter)
{
    std::vector<uint32_t> output;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter)) {
        if (token.size() > 0) {
            output.push_back(std::stoi(token));
        }
    }

    return output;
}

void printBoard(std::vector< std::vector<uint32_t> > board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkBoard(std::vector< std::vector<uint32_t> > board, std::vector<uint32_t> numbers)
{
    int matches = 0;
    int target = board.size();

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            for (int k = 0; k < numbers.size(); k++)
            {

                if (board[i][j] == numbers[k])
                {
                    matches++;
                    if (matches >= target) { return true; }
                }
            }
        }
        matches = 0;
    }
    
    matches = 0;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            for (int k = 0; k < numbers.size(); k++)
            {
                if (board[j][i] == numbers[k])
                {
                    matches++;
                    if (matches >= target) { return true; }
                }
            }
        }
        matches = 0;
    }

    return false;
}

int part1(std::vector< std::vector< std::vector <uint32_t> > > boards, std::vector<uint32_t> numbers)
{
    std::vector<uint32_t> currentNumbers;

    for (int i = 0; i < numbers.size(); i++)
    {
        currentNumbers.push_back(numbers[i]);
        for(int j = 0; j < boards.size(); j++)
        {
            if (checkBoard(boards[j], currentNumbers))
            {
                uint32_t sum = 0;

                // sum all the numbers in current numbers that are in board
                for (int l = 0; l < boards[j].size(); l++)
                {
                    for (int m = 0; m < boards[j][l].size(); m++)
                    {
                        if (!std::count(currentNumbers.begin(), currentNumbers.end(), boards[j][l][m]))
                        {
                            sum += boards[j][l][m];
                        }
                    }
                }

                std::cout << "The winning board is" << std::endl;
                printBoard(boards[j]);
                return sum*currentNumbers[currentNumbers.size()-1];
            }
        }
    }
    return -1;
}

int part2(std::vector< std::vector< std::vector <uint32_t> > > boards, std::vector<uint32_t> numbers)
{
    std::vector<uint32_t> currentNumbers;

    for (int i = 0; i < numbers.size(); i++)
    {
        // std::cout << i << std::endl;
        currentNumbers.push_back(numbers[i]);
        for(int j = boards.size()-1; j >= 0; j--)
        {
            if (checkBoard(boards[j], currentNumbers))
            {
                std::vector< std::vector<uint32_t> > lastToWin;
                lastToWin = boards[j];
                boards.erase(boards.begin() + j);
                
                if (boards.size() == 1)
                {
                    uint32_t sum = 0;

                    // sum all the numbers in current numbers that are in board
                    for (int l = 0; l < lastToWin.size(); l++)
                    {
                        for (int m = 0; m < lastToWin[l].size(); m++)
                        {
                            if (!std::count(currentNumbers.begin(), currentNumbers.end(), lastToWin[l][m]))
                            {
                                sum += lastToWin[l][m];
                            }
                        }
                    }

                    std::cout << "The last board to win is" << std::endl;
                    printBoard(lastToWin);
                    return sum*currentNumbers[currentNumbers.size()-1];
                }
            }
        }
    }
    return -1;
}

int main() 
{
    // Setup
    std::fstream file("input.txt");
    std::string line;
    std::vector<uint32_t> numbers;
    std::vector< std::vector<uint32_t> > currentBoard;
    std::vector< std::vector< std::vector <uint32_t> > > boards;

    while (std::getline(file, line))
    {
        if (numbers.empty())
        {
            numbers = explode(line, ',');
            
        }
        else if (line == "")
        {
            boards.push_back(currentBoard);
            currentBoard.clear();
        }
        else
        {
            currentBoard.push_back(explode(line, ' '));
        }
    }

    boards.push_back(currentBoard);

    // Part 1
    std::cout << "Part 1: " << std::endl;
    int part1Answer = part1(boards, numbers);
    std::cout << "The solution is : " << part1Answer << "\n\n" << std::endl;

    // Part 2
    std::cout << "Part 2: " << std::endl;
    int part2Answer = part2(boards, numbers);
    std::cout << "The solution is : " << part2Answer << std::endl;

    return 0;
}