#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Point {
    int x;
    int y;
};

struct Line {
    Point p1;
    Point p2;
};

static bool operator == (const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

std::vector<Point> overlap(Line l1, Line l2)
{
    std::vector<Point> points;
    for (int x = l1.p1.x; x <= l1.p2.x; x++) {
        for (int y = l1.p1.y; y <= l1.p2.y; y++) {
            Point p = {x, y};
            if (p.x >= l2.p1.x && p.x <= l2.p2.x && p.y >= l2.p1.y && p.y <= l2.p2.y) {
                points.push_back(p);
            }
        }
    }

    return points;
}

int overlappingPoints(std::vector<Line> lines)
{
    std::vector<Point> points;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines.size(); j++) {
            if (i == j) { continue; }
            // std::cout << i << ":" << j << std::endl;
            std::vector<Point> overlappingPoints = overlap(lines[i], lines[j]);
            for (int k = 0; k < overlappingPoints.size(); k++) {
                if (!std::count(points.begin(), points.end(), overlappingPoints[k])) {
                    points.push_back(overlappingPoints[k]);
                }
            }
        }
    }

    return points.size();
}

int main()
{
    // Setup
    std::fstream file("input.txt");
    std::vector<Line> lines;
    std::string input;

    while (getline(file, input))
    {
        std::stringstream ss(input);
        std::string point;
        char delimiter = ' ';
        bool first = true;
        Line l;

        while (getline(ss, point,  ' '))
        {
            if (point != "->")
            {
                int comma = point.find(',');
                if (first)
                {
                    l.p1.x = std::stoi(point.substr(0, comma));
                    l.p1.y = std::stoi(point.substr(comma + 1));
                    first = false;
                }
                else
                {
                    l.p2.x = std::stoi(point.substr(0, comma));
                    l.p2.y = std::stoi(point.substr(comma + 1));
                }

            }
        }
        // std::cout << "(" << l.p1.x << ", " << l.p1.y << "), (" << l.p2.x << ", " << l.p2.y << ")" << std::endl;
        lines.push_back(l);
    }

    // Part 1
    std::cout << "Part 1: There are " << overlappingPoints(lines) << " overlapping points." << std::endl;

    return 0;
}