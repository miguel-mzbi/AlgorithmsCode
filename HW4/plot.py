import matplotlib.pyplot as plt

x = []
y = []
path = "RBTreeResults.txt"

with open(path, 'r') as f:
    for line in f:
        linelist = line.split(",")
        x.append(linelist[0])
        y.append(linelist[1])

print(x)
print(y)

plt.plot(x, y, label = "Time Complexity")
plt.xlabel("n")
plt.ylabel("Time")
plt.title("RBTree")
plt.grid(True)
plt.legend()
plt.show()