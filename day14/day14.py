def parse_input(filename):
    template = []
    rules = []

    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            if not template:
                template = [char for char in str(line)]
            elif line != "":
                rules.append(line.split(' -> ')) 
    
    return template, rules


def fill_template(template, rules, iterations):
    for i in range(iterations):
        print(i)
        t = 0
        while t < len(template)-1:
            for pair in rules:
                if pair[0] == template[t]+template[t+1]:
                    template = template[:t+1] + [pair[1]] + template[t+1:]
                    t += 2
                    break

    return template

def count_letters(string, letters):
    occurences = [0]*len(letters)
    for c in string:
        occurences[letters.index(c)] += 1

    return occurences

def main():
    template, rules = parse_input("input.txt")
    filled_template = fill_template(template, rules, 10)
    count = count_letters(filled_template, ["P", "H", "K", "S", "B", "V", "O", "C", "N", "F"])
    count.sort()
    print("Part 1:\nThe difference between the most and least occuring letters is",
        count[len(count)-1]-count[0]
    )

if __name__ == "__main__":
    main()
