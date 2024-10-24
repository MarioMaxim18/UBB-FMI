def check():
    i = 0
    j = 0
    while i < 10:
        while j < 10:
            if (array_n[i] != 0 and array_m[j] == 0) or (array_n[i] == 0 and array_m[j] != 0):
                return 0
            else:
                i += 1
                j += 1
    return 1

n = int(input())
m = int(input())
array_n = [0] * 10
array_m = [0] * 10
while n > 0:
    digit = n % 10
    array_n[digit] += 1
    n //= 10
while m > 0:
    digit = m % 10
    array_m[digit] += 1
    m //= 10
if check():
    print("Good")
else:
    print("Not good")
