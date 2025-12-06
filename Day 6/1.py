import re
import math

filepath = "./data.txt"
file = open(filepath)
data = file.readlines()

total_sum = 0
pattern = r'[*+]'  


line5 = data[4]
matches = list(re.finditer(pattern, line5))
#print(matches)
for i in range(len(matches)):
    if i != len(matches) - 1:
        col_start = matches[i].start()
        col_end = matches[i+1].start()
    else:
        col_start = col_start = matches[i].start()
        col_end = len(data[0])
    numbers = []
    for j in range(3, -1, -1): 
        numbers.append(int(data[j][col_start:col_end].strip()))
    operator = matches[i].group()
    
    if operator == "*": total_sum += math.prod(numbers)
    if operator == "+": total_sum += sum(numbers)
    


    
    