class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self
    
    def __next__(self):
        x = self.a 
        self.a += 1 # increasing the value of self.a for next iteration
        return x  # and returning the current value for printing or any other purpose
    
    # def __next__(self):
        # if self.a <= 20:
        #     x = self.a
        #     self.a += 1 # increasing the value of self.a for next iteration
        #     return x  # and returning the current value for printing or any other purpose
        # else:
        #     raise StopIteration  # to stop the iteration
    

myclass = MyNumbers()
myiter = iter(myclass)

print(next(myiter))
print(next(myiter))

# for i in MyNumbers():  # continues forever
#     print(i)           