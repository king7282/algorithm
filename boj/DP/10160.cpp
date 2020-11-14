#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000009

char first[7] = " ABCBC", second[7] = " ABABC";
int pi1[7], pi2[7];
int eexp[1000001], dp[1000001][5][5];
int n, k;
int pp[26][7];

void getPi(char* input, int *pi, int size) {
	pi[1] = 0;
	for (int i = 2; i <= size; i++) {
		int next = pi[i - 1];
		while (next > 0 && input[next + 1] != input[i]) {
			next = pi[next];
		}

		if (input[next + 1] == input[i])
			pi[i] = next + 1;
	}

}

int func(int num, int f, int s) {
	if (s == 5 || f == 5) {
		return eexp[n - num + 1];
	}

	if (num == n + 1) {
		return 0;
	}

	if (dp[num][f][s] != -1)
		return dp[num][f][s];

	dp[num][f][s] = 0;
	for (int i = 0; i < 3; i++) {
		std::pair<int, int> next;
		if (first[f + 1] == i + 'A')
			next.first = f + 1;
		else {
			if (i == 0)
				next.first = 1;
			else
				next.first = 0;
		}

		if (second[s + 1] == i + 'A')
			next.second = s + 1;
		else {
			next.second = pp[i][s];
		}

		dp[num][f][s] = (dp[num][f][s] + func(num + 1, next.first, next.second)) % MOD;
	}

	dp[num][f][s] = (dp[num][f][s] + func(num + 1, 0, 0) * (long long)(k - 3) % MOD) % MOD;
	return dp[num][f][s];
}

int main(void) {
	scanf("%d %d", &n, &k);

	eexp[0] = 1;
	for (int i = 1; i <= n; i++)
		eexp[i] = ((long long)eexp[i - 1] * k) % MOD;

	getPi(second, pi2, 5);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 5; j++) {
			if (second[j + 1] == i + 'A') {
				pp[i][j] = j + 1;
			}
			else {
				pp[i][j] = pi2[j];
				while (pp[i][j] > 0 && second[pp[i][j] + 1] != i + 'A')
					pp[i][j] = pi2[pp[i][j]];

				if (second[pp[i][j] + 1] == i + 'A')
					pp[i][j]++;
			}
		}
	}
	memset(dp, -1, sizeof(dp));
	printf("%d\n", (eexp[n] - func(1, 0, 0) + MOD) % MOD);

}