class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def get_name(self):
        return self.name
    
    def get_age(self):
        return self.age
    
    def set_name(self, name):
        self.name = name

    def set_age(self, age):
        self.age = age

    def __str__(self):   # Inheritence
        return "Name: " + self.name + ", Age: " + str(self.age)
    
    def __del__(self):   # Destructor in python
        print("Deleting: " + self.name)
    
class Student(Person):           
    def __init__(self, name, age, gradYear):  # Constructor of child
        super().__init__(name, age)  # Calling super to pass args to parent's constructor
        self.gradYear = gradYear

    def get_gradYear(self):
        return self.gradYear
    
    def __str__(self):
        return super().__str__() + ", Graduation Year: " + str(self.gradYear)

p1 = Student("arsity", 25, 1996)

print(p1.get_name())
print(p1.get_age())

print(p1)
