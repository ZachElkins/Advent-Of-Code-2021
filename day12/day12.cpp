#include <iostream>
#include <fstream>
#include <vector>

struct Node {
    std::vector<Node*> connections = {};
    std::string name;
    bool big; // Big: true, Small: false
    bool visited = false;
};

int findPaths(std::vector<Node*> nodes, Node* start, Node* end) {
    // Find every path from start to end, passing through big false nodes once and type true nodes as many times as needed
    int paths = 0;
    start->visited = true;
    std::vector<Node*> visited = {start};
    std::vector<Node*> toVisit = start->connections;
    while (toVisit.size() > 0) {
        // print out to visit nodes
        for (auto node : toVisit) {
            std::cout << node->name << " ";
        }
        std::cout << std::endl;
        Node* current = toVisit.back();
        toVisit.pop_back();
        if (current == end) {
            paths++;
        }
        current->visited = true;
        for (Node* n : current->connections) {
            if (current->big || !current->visited) {
                toVisit.push_back(n);
                current->visited = true;
            }
        }
    }
    return paths;
}

int main()
{
    // Setup
    std::ifstream file("input0.txt");
    std::string line;
    std::vector<Node*> nodes;
    while (std::getline(file, line)) {
        Node* n = new Node;
        Node* e = new Node;
        int split = line.find('-');
        std::string nodeName = line.substr(0, split);
        std::string edgeName = line.substr(split+1, line.size()-2);

        bool nodeExists = false;
        bool edgeExists = false;
        int nodeIndex = 0;
        int edgeIndex = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->name == nodeName) {
                nodeExists = true;
                nodeIndex = i;
            }
            if (nodes[i]->name == edgeName) {
                edgeExists = true;
                edgeIndex = i;
            }
        }

        if (nodeExists) {
            n = nodes[nodeIndex];
            // std::cout << "(" << nodeIndex << ") Node exists: " << nodeName << std::endl;
        } else {
            n->name = nodeName;
            n->big = std::isupper(nodeName[0]) ? true : false;
            nodes.push_back(n);
        }

        if (edgeExists) {
            e = nodes[edgeIndex];
            // std::cout << "(" << edgeIndex << ") Edge exists: " << edgeName << std::endl;
        } else {
            e->name = edgeName;
            e->big = std::isupper(nodeName[0]) ? true : false;
            nodes.push_back(e);
        }
        n->connections.push_back(e);
        e->connections.push_back(n);
    }

    for (int i = 0; i < nodes.size(); i++) {
        std::cout << nodes[i]->name << ": (";
        std::cout << nodes[i]->big << ") -> ";
        std::cout << "{ ";
        for (int j = 0; j < nodes[i]->connections.size(); j++) {
            std::cout << nodes[i]->connections[j]->name << "-";
            std::cout << &nodes[i]->connections[j] << ", ";
        }
        std::cout << " }" << std::endl;
    }

    // Part 1
    Node* start;
    Node* end;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->name == "start") {
            start = nodes[i];
        }
        if (nodes[i]->name == "end") {
            end = nodes[i];
        }
    }

    int paths = findPaths(nodes, start, end);
    std::cout << paths << std::endl;

    return 0;
}