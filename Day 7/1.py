filepath = "input.txt"

startidx = 0

def find_spit(line):
    print(startidx)


with open(filepath) as f:
    lines = f.readlines()
    startidx = lines[0].find("S")
    find_spit(lines[0])
