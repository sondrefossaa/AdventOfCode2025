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
    for j in range(i+1, len(data)):
        for valid_range in valid_ranges:
            if valid_range[0] <= int(data[j]) <= valid_range[1]+1:
                answer += 1
                break
        
    print(answer)