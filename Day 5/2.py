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
    for start, end in valid_ranges:
        for seen_range in seen_id_range:
            if start >= seen_range[0] and end <= seen_range[1]:
                seen_id_range = [min(seen_id_range[0], start), max(seen_id_range[1], end+1)]
            else:
                seen_id_range.append(start, end)
    answer = seen_id_range[1] - seen_id_range[0] + 1
        
    print(answer)