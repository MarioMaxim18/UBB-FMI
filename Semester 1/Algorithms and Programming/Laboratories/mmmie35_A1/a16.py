ok = 1
i = 0
while ok == 1:
    n=int(input("n="))
    if n % 10 < n // 10 % 10:
        i += 1
    if n == 0:
        ok = 0
print (i)
