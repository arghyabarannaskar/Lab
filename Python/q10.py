def isOdd(n):
    return n % 2 != 0

def square(x):
    return x*x

lst = list(filter(isOdd, list(map(square, [x for x in range(11)]))))

print(lst)