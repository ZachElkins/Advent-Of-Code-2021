import sys

def parseInput(filename):
    graph = {}
    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            vecs = line.split('-')
            if vecs[0] in graph:
                graph[vecs[0]].append(vecs[1])
            else:
                graph[vecs[0]] = [vecs[1]]
            if vecs[1] in graph:
                graph[vecs[1]].append(vecs[0])
            else:
                graph[vecs[1]] = [vecs[0]]
    return graph

def count_paths(graph: dict, current: str, visited: set):
    if (current == "end"): return 1
    
    paths = 0
    for vec in graph[current]:
        if vec not in visited:
            if not vec.isupper(): visited.add(vec)
            paths += count_paths(graph, vec, visited)
            if not vec.isupper(): visited.remove(vec)
    
    return paths

def count_paths2(graph: dict, current: str, visited: set, double_small: bool):
    if (current == "end"): return 1
    
    paths = 0
    for vec in graph[current]:
        if vec not in visited:
            if not vec.isupper(): visited.add(vec)
            paths += count_paths2(graph, vec, visited, double_small)
            if not vec.isupper(): visited.remove(vec)
        elif not double_small and vec != "start":
            paths += count_paths2(graph, vec, visited, True)
    
    return paths

def main(part):
    graph = parseInput('input.txt')
    
    if part == 1 or part == -1:
        paths = count_paths(graph, "start", {"start"})
        print(f"Part 1:\nThere are {paths} paths.")

    if part == 2 or part == -1:
        paths = count_paths2(graph, "start", {"start"}, False)
        print(f"Part 2:\nThere are {paths} paths.")
    


if __name__ == "__main__":
    part = -1

    if (len(sys.argv) > 1):
        part = int(sys.argv[1])
    
    if part not in {-1, 1, 2}:
        print("Usage: day12.py [part]")
        print("\tpart: 1 or 2")
        exit(1)
    else:
        main(part)