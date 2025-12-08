filepath = "Day 3\data.txt"

total = 0
def get_biggest(line):
    int_list = list(map(int, line))
    biggest = max(int_list)
    biggest_indx = int_list.index(biggest)
    if biggest_indx + 1 == len(int_list):
        return max(int_list[:biggest_indx]) * 10 + biggest
    return biggest * 10 + max(int_list[biggest_indx + 1:])   


with open(filepath) as f:
    for line in f:
        total += get_biggest(line.strip())

print(total)