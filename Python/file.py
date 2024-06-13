f = open("text.txt", "rt")

# while True:
#     data = f.readline()
#     print(data)
#     break

for data in f:
    print(data)

f.seek(0, 0)

data = f.read()
print(data)

f.close()