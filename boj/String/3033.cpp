#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#define X 255
#define MOD 100003

char input[200010];
int n;
std::vector<int> str[100003];

bool OK(int num) {
	for (int i = 0; i < MOD; i++)
		str[i].clear();

	long long hash = 0, t = 1;

	for (int i = 1; i <= num; i++) {
		hash = (hash * X + input[i]) % MOD;
		if (i != 1)
			t = (t * X) % MOD;
	}

	str[hash].push_back(num);
	for (int i = num + 1; i <= n; i++) {
		hash = ((hash - input[i - num] * t % MOD + MOD) % MOD * X % MOD + input[i]) % MOD;

		bool flag = false;

		for (int j = 0; j < str[hash].size() && !flag; j++) {
			bool flag2 = false;
			for (int k = 0; k < num && !flag2; k++) {
				if (input[str[hash][j] - k] != input[i - k])
					flag2 = true;
			}

			if (!flag2)
				flag = true;
		}

		if (flag)
			return true;
		str[hash].push_back(i);
	}
	return false;
}

int main(void) {
	scanf("%d", &n);
	getchar();

	for (int i = 1; i <= n; i++) {
		scanf("%c", input + i);
	}

	int s = 1, e = n - 1, r = 0;
	while (s <= e) {
		int mid = (s + e) / 2;

		if (OK(mid)) {
			s = mid + 1;
			r = std::max(r, mid);
		}
		else
			e = mid - 1;
	}

	printf("%d\n", r);
}