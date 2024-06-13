class Person:
    def __init__(self, name, age):
        self.name =name
        self.age = age

    def __str__(self):
        return "name: "+self.name+", age: "+str(self.age)
    
    def setData(self, name, age):
        self.name = name
        self.age = age

    def __del__(self):
        print("Deleting object: "+ str(self))


p1 = Person("Arghya", 24)
print(p1)
p2 = p1
p2.setData("Bonu", 16)
print(p2)
print(p1)