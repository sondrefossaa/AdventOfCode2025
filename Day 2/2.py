input="9191906840-9191941337,7671-13230,2669677096-2669816099,2-12,229599-392092,48403409-48523311,96763-229430,1919163519-1919240770,74928-96389,638049-668065,34781-73835,736781-819688,831765539-831907263,5615884-5749554,14101091-14196519,7134383-7169141,413340-625418,849755289-849920418,7745350-7815119,16717-26267,4396832-4549887,87161544-87241541,4747436629-4747494891,335-549,867623-929630,53-77,1414-3089,940604-1043283,3444659-3500714,3629-7368,79-129,5488908-5597446,97922755-98097602,182-281,8336644992-8336729448,24-47,613-1077"

numarr = input.split(",")
total_sum = 0

for item in numarr:
    start, end = item.split("-")
    start_int = int(start)
    end_int = int(end)
    
    for num in range(start_int, end_int + 1):
        numstr = str(num)
        isRepeating = False
        for step in range(1, len(numstr)//2 + 1):
            if len(numstr) % step != 0:
                continue
            if numstr == numstr[:step] * (len(numstr) // step):
                isRepeating = True
                        
        if isRepeating:
            total_sum += num


print(total_sum)