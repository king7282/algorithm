def solve() :
    n, m = map(int, input().strip().split(" "))
    
    dp = [[0]*101 for _ in range(101)]

    dp[0][0] = 1
    for i in range(1, n + 1):
        dp[i][0] = 1
        for j in range(1, i + 1) :
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]

    print(dp[n][m])

solve()
