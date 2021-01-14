
def solve() :
    n, m, k = map(int, input().strip().split(" "))
    
    fac = [1 for _ in range(0, n + m + 1)]

    for i in range(1, n + m + 1) :
        fac[i] = fac[i - 1] * i

    if fac[n + m] / (fac[n] * fac[m]) < k :
        print(-1)
        return
    
    result = []
    
    a = n
    z = m

    for i in range(0, n + m) :
        if a == 0:
            result.append('z')
        else:
            remain = fac[a + z - 1] / (fac[a - 1] * fac[z])

            if remain >= k :
                a -= 1
                result.append('a')
            else :
                z -= 1
                k -= remain
                result.append('z')
    
    for i in result :
        print(i, end='')

solve()
