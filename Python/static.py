class Fruit:
    count = 0

    def __init__(self, name = '', size = 0, color = ''):
        self._name = name
        self._size = size
        self._color = color
        Fruit.count += 1

    def display():
        print("Total "+str(Fruit.count)+" fruits created")

f1 = Fruit('Banana', 5, 'Yellow')
f1 = Fruit('Orange', 5, 'orange')
Fruit.display()

    