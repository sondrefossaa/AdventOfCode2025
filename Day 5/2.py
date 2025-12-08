filepath = "./input.txt"
answer = 0
with open(filepath) as f:
    data = f.readlines()
    valid_ranges = []
    
    i = 0
    line = data[i].strip()
    while line != "":
        valid_ranges.append(list(map(int, line.split("-"))))
        i += 1
        line = data[i].strip()
    seen_id_range = []
    valid_ranges.sort()
    merged = []

    for start, end in valid_ranges:
        if not merged or start > merged[-1][1] + 1:
            merged.append([start, end])
        else:
            merged[-1][1] = max(merged[-1][1], end)

    answer = sum(end - start + 1 for start, end in merged)
    print(answer)
