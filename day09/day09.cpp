#include <iostream>
#include <fstream>
#include <vector>

struct Point {
    int val;
    bool visited = false;
};

std::vector< std::vector<Point> > gridToPoints(std::vector< std::vector<int> > grid) {
    std::vector< std::vector<Point > > coords;
    for (int i = 0; i < grid.size(); i++) {
        std::vector<Point> row;
        for (int j = 0; j < grid[i].size(); j++) {
            Point c;
            c.val = grid[i][j];
            row.push_back(c);
        }
        coords.push_back(row);
    }

    return coords;
}


bool isMin(std::vector< std::vector<Point> > heights, std::vector< std::vector<int> > adjacents, int x, int y) {
    
    int current = heights[x][y].val;
    
    for(int i = 0; i < adjacents.size(); i++) {
        if (heights[adjacents[i][0]][adjacents[i][1]].val <= current) {
            return false;
        }
    }
    
    return true;
}

std::vector<std::vector<int> > getAdjacents(std::vector< std::vector<Point> > heights, int x, int y) {
    std::vector< std::vector<int> > adjacents;
    
    if (x > 0) { adjacents.push_back({x - 1, y}); }
    if (x < heights.size() - 1) { adjacents.push_back({x + 1, y}); }
    if (y > 0) { adjacents.push_back({x, y - 1}); }
    if (y < heights[x].size() - 1) { adjacents.push_back({x, y + 1}); }
            
    return adjacents;
}

std::vector< std::vector<int> > lowPointCoords(std::vector< std::vector<Point> > heights)
{
    std::vector< std::vector<int >> coords;
    for (int x = 0; x < heights.size(); x++)
    {
        for (int y = 0; y < heights[x].size(); y++)
        {
            if (isMin(heights, getAdjacents(heights, x, y), x, y)) { coords.push_back({x, y}); }
        }
    }
    return coords;
}

int riskLevel(std::vector< std::vector<Point> > heights, std::vector< std::vector<int> > coords)
{
    int risk = 0;
    
    for (int i = 0; i < coords.size(); i++) {
        risk += heights[coords[i][0]][coords[i][1]].val;
    }
    risk = risk + coords.size();

    return risk;
}

int exploreBasin(std::vector< std::vector<Point> > heights, int x, int y)
{
    Point *current = &heights[x][y];
    // std::cout << "Called Explore Basin: " << "(" << x << "," << y  << ") -> " << current->val << std::endl;

    int size = 1;

    current->visited = true;

    std::vector< std::vector<int> > adjacents = getAdjacents(heights, x, y);

    // recursivly return the number of adjacent items that are not 9

    for (int i = 0; i < adjacents.size(); i++) {
        Point *coord = &heights[adjacents[i][0]][adjacents[i][1]];
        if (coord->visited == false && coord->val < 9 && coord->val-1 == current->val) {
            // coord->visited = true;
            coord->visited = true;
            // heights[adjacents[i][0]][adjacents[i][1]] = *coord;
            std::cout << "(" << adjacents[i][0] << "," << adjacents[i][1]  << ") -> " << coord->val << " +1" << coord->visited << std::endl;
            size = size + exploreBasin(heights, adjacents[i][0], adjacents[i][1]);
        }
    }
    return size;
}

std::vector<int> basins(std::vector< std::vector<Point> > heights, std::vector< std::vector<int> > lowPoints)
{
    std::cout << "Called Basin" << std::endl;

    std::vector<int> basinSizes;
    
    for (int i = 0; i < lowPoints.size(); i++) {
        int x = lowPoints[i][0];
        int y = lowPoints[i][1];
        std::cout << "NEW BASIN" << std::endl;
        // for (int x = 0; x < heights.size(); x++) {
        //     for (int y = 0; y < heights[x].size(); y++) {
        //         Point *p = &heights[x][y];
        //         p->visited = false;
        //     }
        // }
        basinSizes.push_back(exploreBasin(heights, x, y));
    }
    
    // print out the basin sizes
    std::cout << "Basin sizes: ";
    for (int i = 0; i < basinSizes.size(); i++) {
        std::cout << basinSizes[i] << " ";
    }

    std::cout << "Returning Basin" << std::endl;
    return basinSizes;
}


int main()
{
    // Setup
    std::ifstream file("input.txt");
    std::string line;
    std::vector< std::vector<int> > heights;

    while (file >> line)
    {
        std::vector<int> row;
        for (int i = 0; i < line.size(); i++) { row.push_back((int)(line[i]-'0')); }
        heights.push_back(row);
    }

    std::vector< std::vector<int> > newHeights {
        {2,1,9,9,9,4,3,2,1,0},
        {3,9,8,7,8,9,4,9,2,1},
        {9,8,5,6,7,8,9,8,9,2},
        {8,7,6,7,8,9,6,7,8,9},
        {9,8,9,9,9,6,5,6,7,8},
    };

    // Part 1
    std::vector< std::vector <Point> > pointGrid = gridToPoints(newHeights);
    std::vector< std::vector<int> > coords = lowPointCoords(pointGrid);
    int risk = riskLevel(pointGrid, coords);
    std::cout << "Part 1:\nThe total risk level is " << risk << "!" << std::endl;
    
    // Part 2
    std::vector<int> allBasins = basins(pointGrid, coords);
    for (int i = 0; i < allBasins.size(); i++) {
        std::cout << "Basin " << i << ": " << allBasins[i] << std::endl;
    }
    std::cout << "Part 1:\nThe total risk level is " << risk << "!" << std::endl;

    return 0;
}