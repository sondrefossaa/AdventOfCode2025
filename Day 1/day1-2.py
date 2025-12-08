from itertools import repeat
count = 0
tall = 50
with open ("./file.txt", "r") as data:
    linjer = data.readlines()
    for linje in linjer:
        linje = linje.strip()
        dir = linje[0]
        rotasjon = int(linje[1:])
        match dir:
            case "R":
                for _ in repeat(None, rotasjon):
                    tall += 1
                    count += tall%100==0
            case "L":
                for _ in repeat(None, rotasjon):
                    tall -= 1
                    count += tall%100==0


        
print(count)