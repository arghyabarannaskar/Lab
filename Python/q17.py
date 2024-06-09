import heapq

class PriorityQueue:
    def __init__(self):
        self.heap = []
        self.index = 0

    def push(self, item, priority):
        heapq.heappush(self.heap, (-priority, self.index, item))
        self.index += 1

    def pop(self):
        _, _, item = heapq.heappop(self.heap)
        return item

pq = PriorityQueue()
pq.push('Task 1', 5)
pq.push('Task 2', 3)
pq.push('Task 3', 7)
pq.push('Task 4', 1)

print(pq.pop())  
print(pq.pop())  
print(pq.pop())  
print(pq.pop())  
