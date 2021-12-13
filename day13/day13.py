import itertools
import sys

def parseInput(filename):
    dots = []
    folds = []
    fold = False

    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            if line == "":
                fold = True
                continue
            if not fold:
                coord = line.split(',')
                dots.append([int(coord[0]), int(coord[1])])
            else:
                fold_instruction = line.split(' ')
                fold_position = fold_instruction[-1].split('=')
                folds.append([fold_position[0], int(fold_position[1])])

    return dots, folds

def fold(dots, fold):
    ax = 0 if fold[0] == "x" else 1
    folded_dots = []

    i = len(dots) - 1
    while i > 0:

        if dots[i][ax] > fold[1]:
            dist = dots[i][ax] - fold[1]
            test_dot = dots[i].copy()
            test_dot[ax] = fold[1]-dist
            if test_dot in dots:
                dots.remove(test_dot)
            if test_dot not in folded_dots:
                folded_dots.append(test_dot)
        else:
            if dots[i][ax] not in folded_dots:
                folded_dots.append(dots[i])

        i -= 1

    return folded_dots

def all_folds(dots, folds):
    folded_dots = dots
    for op in folds:
        folded_dots = fold(folded_dots, op)
    
    return folded_dots

def print_dots(dots):
    max_x = max_y = 0
    for dot in dots:
        if dot[0] > max_x:
            max_x = dot[0]
        if dot[1] > max_y:
            max_y = dot[1]

    for y in range(0, max_y+1):
        for x in range(0, max_x+1):
            out = "#" if [x, y] in dots else "."
            print(out, end="")
        print()

def main(part):
    dots, folds = parseInput('input.txt')
    
    if part == 1 or part == -1:
        one_fold = fold(dots.copy(), folds[0])
        print(f"Part 1:\nThe first fold leaves {len(one_fold)+1} dots.")


    if part == 2 or part == -1:
        folded_dots = all_folds(dots.copy(), folds)
        # print_dots(one_fold)
        print(f"Part 2:\nThe code is:") #FGKCKBZG
        print_dots(folded_dots)

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