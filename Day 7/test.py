import copy
path = './input.txt'

data = [list(line.rstrip("\n")) for line in open(path)]

def project_beam(col: int, row:int, data: list[int], visited) -> None:
    total = 0
    while data[row][col] != "^":
        row += 1
        if row == len(data):
            return 1
    
    if visited[row][col] == "^":
        total += project_beam(col + 1, row, data, visited)
        total += project_beam(col - 1, row, data, visited)
        visited[row][col] = total
        return total
    else:
        return visited[row][col]

s = data[0].index("S")
visited = copy.deepcopy(data)
print(project_beam(s, 1, data, visited))
