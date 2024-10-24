n = int(input())
a = []
while n:
    a.append(n%10)
    n = n // 10
a.sort()
x = 0
for i in range(len(a)):
    if a[i] != 0:
        x = i
        break
temp = a[0]
a[0] = a[x]
a[x] = 0
answer = 0
for i in range(len(a)):
    answer *= 10
    answer += a[i]
print(answer)