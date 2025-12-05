filepath = "Day 3\data.txt"
total = 0
NUM_LEN = 12

def find_sub_num(interval):
    interval_str = list(map(str, interval))
    newlist = []
    biggest = list(map(str, sorted(interval, reverse=True)))[:NUM_LEN+1]
    return biggest
    result = filter(interval, biggest)
    
    result = "".join(map(str, new_list))
    return int(result)

def get_biggest(row):
    int_list = list(map(int, row))
    list_len = len(int_list)
    biggest = max(int_list)
    biggest_indx = int_list.index(biggest)
    # If biggest number can satisfy numlen, return it
 
    pos_nums = []
    l = int_list[:biggest_indx]

    new_max = max(l)
    #new_max_idx = l.index(new_max)
    #print(new_max)
    for i in range(0, list_len + 1 - NUM_LEN):
        if int_list[i] == new_max:
            pos_nums.append(find_sub_num(int_list[i:]))
    return max(pos_nums)

""" with open(filepath) as f:
    for row in f:
        total += get_biggest(row.strip()) """

print(find_sub_num([1,2,3,4,5,6,7,8,9,6,6,1,2]))