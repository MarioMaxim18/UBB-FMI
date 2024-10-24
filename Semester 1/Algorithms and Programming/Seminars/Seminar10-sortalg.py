#SELECTION SORT 
def selectionSort(lst):
    for i in range(len(lst)-1, 0, -1):
        max_pos = 0
        for j in range(1, i + 1):
            if lst[j] > lst[max_pos]:
                max_pos = j
        lst[i], lst[max_pos] = lst[max_pos], lst[i]
    return lst

lst1 = [23, 20, 16, 12, 7]
print("Selection sort for ", lst1)
print(", sorted list is: ", selectionSort(lst1))
         

#INSERTION SORT
def insertionSort(lst):        
    for i in range(1, len(lst)): 
        item_to_insert = lst[i]
        j = i-1
        while j >= 0 and lst[j] > item_to_insert:
            lst[j+1] = lst[j]
            j -= 1
        lst[j+1] = item_to_insert
    return lst

lst = [54,26,93,17,77,31,44,55,20]
insertionSort(lst)
print(lst)


#BUBBLE SORT
def bubbleSort(lst):
    for i in range(len(lst)):
        for j in  range(len(lst)-i-1):
            if lst[j] > lst[j+1]:
                lst[j], lst[j+1] = lst[j+1], lst[j]
    return lst
    
lst2 = [23, 20, 16, 12, 7]
print("Bubble sort for ", lst2)
print(", sorted list is: ", bubbleSort(lst2))


#QUICKSORT
from random import randint
def quicksort(lst):
    if len(lst) <= 1:
        return lst
    
    index = randint(0, len(lst)-1)
    pivot = lst[index]
    
    lower, same, higher = [], [], []
    for elem in lst:
        if elem < pivot:
            lower.append(elem)
        elif elem == pivot:
            same.append(elem)
        else:
            higher.append(elem)
    return quicksort(lower) + same + quicksort(higher)


lst3 = [23, 20, 16, 12, 7]
print("Quick sort for ", lst3)
print(", sorted list is: ", quicksort(lst3))






