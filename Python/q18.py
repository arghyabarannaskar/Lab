import heapq

def largest_N(collection, N):
    return heapq.nlargest(N, collection)

def smallest_N(collection, N):
    return heapq.nsmallest(N, collection)


collection = [10, 5, 8, 20, 3, 15]
N = 3

largest_items = largest_N(collection, N)
smallest_items = smallest_N(collection, N)

print("Largest", N, "items:", largest_items)
print("Smallest", N, "items:", smallest_items)
