def isPrime(n):
    d = 2;
    if (n == 1):
        return False
    while (d < n):
        if n % d == 0:
            return False
        d = d + 1
    return True

n = int(input())
a1 = 0
a2 = 0
for i in range(n + 1, n + 10):
    if isPrime(i):
        a2 = i
        break
for i in range(n - 1, 1, -1):
    if isPrime(i):
        a1 = i
        break
if n - a1 > a2 - n:
    print (a2)
else:
    print (a1)