'''Print Graham Plot'''
import matplotlib.pyplot as plt

def main():
    ''' Main function for module'''

    pathC = "GrahamCoords.txt"
    pathH = "GrahamHulls.txt"

    plt.clf()
    x = []
    y = []
    hx = []
    hy = []

    with open(pathC, 'r') as f:
        for line in f:
            linelist = line.split(",")
            x.append(int(linelist[0]))
            y.append(int(linelist[1]))

    print(x)
    print(y)

    with open(pathH, 'r') as f:
        for line in f:
            linelist = line.split(",")
            hx.append(linelist[0])
            hy.append(linelist[1])
    hx.append(hx[0])
    hy.append(hy[0])

    print(hx)
    print(hy)

    plt.title("Graham Scan 1000 point plot")
    plt.plot(x, y, 'bo')
    plt.plot(hx, hy, 'b-')
    plt.show()

if __name__ == "__main__":
    main()
