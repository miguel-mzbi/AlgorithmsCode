def combSort(A):
    gap = len(A)
    swapped = True
    shrinkFactor = 1.3
    if gap < 2:
        return
    while gap > 1 or swapped:
        gap = int(gap/shrinkFactor)
        swapped = False
        for i in range(0, len(A) - gap):
            if A[i] > A[i+gap]:
                A[i], A[i+gap] = A[i+gap], A[i]
                swapped = True
                print(A)

Array = [33, 98, 74, 13, 55, 20, 77, 45, 64, 83]
print("Sorting:")
print(Array)
combSort(Array)
print("Sorted!:")
print(Array)
