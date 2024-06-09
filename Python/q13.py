import time

def geometric_progression(a, q):
    term = a
    while term <= 100000:
        yield term
        term *= q

# Example usage
a = 2
q = 3

# Measure the total time and time within the loop
start_total = time.time()
start_loop = None

for term in geometric_progression(a, q):
    if start_loop is None:
        start_loop = time.time()
    print(term)

end_loop = time.time()
end_total = time.time()

total_time = end_total - start_total
loop_time = end_loop - start_loop

print(f"Total time: {total_time:.6f} seconds")
print(f"Time within the loop: {loop_time:.6f} seconds")
