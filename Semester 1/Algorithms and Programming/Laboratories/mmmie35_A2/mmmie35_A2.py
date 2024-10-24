score_list = []

def read_file():
    with open("input", "r") as file:
        content = file.read()
        lst = content.split(" ")
    for i in lst:
        score_list.append(int(i))
    return score_list

def write_file(list):
    str1 = ""
    for i in list:
        str1 += str(i) + " "
    with open("output", "w") as file:
        file.write(str1)

history = []
history.append(score_list.copy())

"""
Description: THE FUNCTION ADD A VALUE AS LAST ELEMENT IN MY LIST
Input: THE LIST AND THE VALUE
Output: THE LIST WITH THE NEW VALUE"""
def add(score_list, value):
    score_list.append(value)
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION ADD A VALUE AT A SPECIFIC INDEX
Input: THE LIST, THE INDEX AND THE VALUE
Output: THE LIST WITH THE NEW VALUE AT THE SPECIFIC INDEX
"""
def insert(score_list, index, value):
    score_list.insert(index, value)
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION REMOVE A VALUE AT A SPECIFIC INDEX
Input: THE LIST AND THE INDEX
Output: THE LIST WITHOUT THE VALUE AT THE SPECIFIC INDEX
"""
def remove(score_list, index):
    score_list.pop(index)
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION REMOVE ELEMENTS FROM 2 SPECIFIC INDEXES
Input: THE LIST, THE FROM INDEX AND THE TO INDEX
Output: THE LIST WITHOUT THE VALUES FROM THE SPECIFIC INDEXES
"""
def remove_between(score_list, from_index, to_index):
    for i in range(to_index, from_index - 1, -1):
        score_list.pop(i)
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION REPLACE A VALUE FROM A SPECIFIC INDEX WITH A NEW ONE
Input: THE LIST, THE INDEX AND THE NEW VALUE
Output: THE LIST WITH THE NEW VALUE AT THE SPECIFIC INDEX
"""
def replace(score_list, index, new_value):
    score_list[index] = new_value
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION RETURN THE VALUES LESS THAN A SPECIFIC VALUE
Input: THE LIST AND THE VALUE
Output: THE VALUES LESS THAN A SPECIFIC VALUE
"""
def less(score_list, value):
    for i in range(len(score_list)):
        if score_list[i] < value:
            print(score_list[i])

"""
Description: THE FUNCTION SORT THE LIST
Input: THE LIST
Output: THE SORTED LIST
"""
def sorted(score_list):
    score_list.sort()
    history.append(score_list.copy())
    return score_list

"""
Description: THE FUNCTION RETURN THE VALUES HIGHER THAN A SPECIFIC VALUE
Input: THE LIST AND THE VALUE
Output: THE VALUES HIGHER THAN A SPECIFIC VALUE
"""
def sorted_higher(score_list, value):
    new_list=[]
    for i in range(len(score_list)):
        if score_list[i] > value:
            new_list.append(score_list[i])
    new_list.sort()
    print(new_list)

"""
Description: THE FUNCTION RETURN THE AVERAGE OF THE VALUES FROM 2 SPECIFIC INDEXES
Input: THE LIST, THE FROM INDEX AND THE TO INDEX
Output: THE AVERAGE OF THE VALUES FROM 2 SPECIFIC INDEXES
"""
def avg(score_list, from_index, to_index):
    sum = 0
    for i in range(from_index, to_index + 1):
        sum += score_list[i]
    print(sum / (to_index - from_index + 1))

"""
Description: THE FUNCTION RETURN THE MINIMUM VALUE FROM 2 SPECIFIC INDEXES
Input: THE LIST, THE FROM INDEX AND THE TO INDEX
Output: THE MINIMUM VALUE FROM 2 SPECIFIC INDEXES
"""
def min(score_list, from_index, to_index):
    min = score_list[from_index]
    for i in range(from_index, to_index + 1):
        if score_list[i] < min:
            min = score_list[i]
    print(min)

"""
Description: THE FUNCTION RETURN THE VALUES THAT ARE MULTIPLE OF 10 FROM 2 SPECIFIC INDEXES
Input: THE LIST, THE FROM INDEX AND THE TO INDEX
Output: THE VALUES THAT ARE MULTIPLE OF 10 FROM 2 SPECIFIC INDEXES
"""
def mul(score_list, from_index, to_index):
    for i in range(from_index, to_index + 1):
        if score_list[i] % 10 == 0:
            print(score_list[i])

"""
Description: THE FUNCTION KEEP ONLY THE VALUES THAT ARE MULTIPLE OF A SPECIFIC VALUE
Input: THE LIST AND THE VALUE
Output: THE VALUES THAT ARE MULTIPLE OF A SPECIFIC VALUE
"""
def filter_mul(score_list, value):
    new_score_list = []
    for i in range(len(score_list)):
        if score_list[i] % value == 0:
            new_score_list.append(score_list[i])
    score_list = new_score_list
    return score_list

"""
Description: THE FUNCTION KEEP ONLY THE VALUES THAT ARE GREATER THAN A SPECIFIC VALUE
Input: THE LIST AND THE VALUE
Output: THE VALUES THAT ARE GREATER THAN A SPECIFIC VALUE
"""
def filter_greater(score_list, value):
    new_score_list = []
    for i in range(len(score_list)):
        if score_list[i] > value:
            new_score_list.append(score_list[i])
    score_list = new_score_list
    return score_list

"""
Description: THE FUNCTION UNDO THE LAST ACTION
Input: THE LIST
Output: THE LIST BEFORE THE LAST ACTION
"""
def undo():
    history.pop()
    score_list = history[-1]
    return score_list

ans = True
while ans:
    print("""
    1.Add
    2.Insert
    3.Remove
    4.Remove between
    5.Replace
    6.Less
    7.Sorted
    8.Sorted higher
    9.Average
    10.Min
    11.Multiple of 10
    12.Filter multiple
    13.Filter greater
    14.Undo
    0.Exit
    """)
    ans = input("What would you like to do? ")
    if ans == "1":
        value = int(input("Enter value: "))
        list = read_file()
        print(add(score_list, value))
        write_file(score_list)

    elif ans == "2":
        index = int(input("Enter index: "))
        value = int(input("Enter value: "))
        print(insert(score_list, index, value))
    elif ans == "3":
        index = int(input("Enter index: "))
        print(remove(score_list, index))
    elif ans == "4":
        from_index = int(input("Enter from index: "))
        to_index = int(input("Enter to index: "))
        print(remove_between(score_list, from_index, to_index))
    elif ans == "5":
        index = int(input("Enter index: "))
        value = int(input("Enter value: "))
        print(replace(score_list, index, value))
    elif ans == "6":
        value = int(input("Enter value: "))
        less(score_list, value)
    elif ans == "7":
        print(sorted(score_list))
    elif ans == "8":
        value = int(input("Enter value: "))
        sorted_higher(score_list, value)
    elif ans == "9":
        from_index = int(input("Enter from index: "))
        to_index = int(input("Enter to index: "))
        avg(score_list, from_index, to_index)
    elif ans == "10":
        from_index = int(input("Enter from index: "))
        to_index = int(input("Enter to index: "))
        min(score_list, from_index, to_index)
    elif ans == "11":
        from_index = int(input("Enter from index: "))
        to_index = int(input("Enter to index: "))
        mul(score_list, from_index, to_index)
    elif ans == "12":
        value = int(input("Enter value: "))
        print(filter_mul(score_list, value))
    elif ans == "13":
        value = int(input("Enter value: "))
        print(filter_greater(score_list, value))
    elif ans == "14":
        print(undo())
    elif ans == "0":
        break