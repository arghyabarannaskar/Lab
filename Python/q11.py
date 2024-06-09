import math

pairsOfSmallest2 = [(a, b) for a in range(1, 10) for b in range(a, 10)]

def isValid(element):
    a, b = element
    return math.sqrt(a ** 2 + b ** 2) == int(math.sqrt(a ** 2 + b ** 2))

validPairs = list(filter(isValid, pairsOfSmallest2))

validTriplets = [(a, b, int(math.sqrt(a ** 2 + b ** 2))) for (a, b) in validPairs]

print(validTriplets)