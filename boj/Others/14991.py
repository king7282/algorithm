n = int(input())

arr = []

tmp = input().split(" ")
for num in tmp:
    if num.isdigit() :
        arr.append(int(num))

prev = 1
flag = 1

for i in range(n):
    prev = prev * 2
    if prev < arr[i]:
        flag = 0
        break
    prev -= arr[i]


if flag == 0 :
    print("error")
else:
    print(prev % 1000000007)