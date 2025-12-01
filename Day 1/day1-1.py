count = 0
tall = 50
with open ("./file.txt") as data:
    linjer = data.readlines()
    for linje in linjer:
        linje = linje.strip()
        dir = linje[0]
        rotasjon = int(linje[1:])
        match dir:
            case "R":
                tall = (tall + rotasjon) % 100
            case "L":
                tall = (tall - rotasjon) % 100
        if tall == 0:
            count += 1
print(count)
