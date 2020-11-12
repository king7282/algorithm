#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#define MOD 1000000007

struct info {
	int num, x1, x2;
	info(int num, int x1, int x2) : num(num), x1(x1), x2(x2) {}
};

int n, k1, k2, pi1[10010], pi2[10010], eexp[100010];
char input1[10010], input2[10010];
int dp1[10000010], dp2[100000010], dp3[10000010];
std::vector<std::pair<int, int>> next1, next2;

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

int func1(int num, int x1, int x2) {
	if (x1 == k1 || x2 == k2)
		return eexp[n - num + 1];

	if (num == n + 1)
		return 0;

	int tmp = num - 1 + x1 * n + x2 * k1 * n;
	if (dp1[tmp] != -1)
		return dp1[tmp];

	int &r = dp1[tmp];
	r = (func1(num + 1, next1[x1].first, next2[x2].first) + func1(num + 1, next1[x1].second, next2[x2].second)) % MOD;

	return r;
}

int func2(int num, int x) {
	if (x == k2)
		return eexp[n - num + 1];

	if (num == n + 1)
		return 0;

	int tmp = num - 1 + x * n;
	if (dp2[tmp] != -1)
		return dp2[tmp];

	return dp2[tmp] = (func2(num + 1, next2[x].first) + func2(num + 1, next2[x].second)) % MOD;
}

int func3(int num, int x) {
	if (x == k1)
		return eexp[n - num + 1];

	if (num == n + 1)
		return 0;

	int tmp = num - 1 + x * n;
	if (dp3[tmp] != -1)
		return dp3[tmp];

	int &r = dp3[tmp];
	r = (func3(num + 1, next1[x].first) + func3(num + 1, next1[x].second)) % MOD;

	return r;
}


int main(void) {
	scanf("%d %d %d", &n, &k1, &k2);
	
	for (int i = 1; i <= k1; i++)
			scanf(" %c", input1 + i);


	for (int i = 1; i <= k2; i++)
		scanf(" %c", input2 + i);

	eexp[0] = 1;
	for (int i = 1; i <= n; i++)
		eexp[i] = (eexp[i - 1] * 2) % MOD;

	if (k1 == 0 && k2 == 0) {
		printf("0\n");
		return 0;
	}
	if (k1 == 0 || k1 > n) {
		if (k1 == 0) {
			getPi(input2, pi2, k2);
			next2.resize(k2);

			for (int i = 0; i < k2; i++) {
				next2[i].first = next2[i].second = i;

				while (next2[i].first > 0 && input2[next2[i].first + 1] != '0')
					next2[i].first = pi2[next2[i].first];

				if (input2[next2[i].first + 1] == '0')
					next2[i].first++;

				while (next2[i].second > 0 && input2[next2[i].second + 1] != '1')
					next2[i].second = pi2[next2[i].second];

				if (input2[next2[i].second + 1] == '1')
					next2[i].second++;
			}

			memset(dp2, -1, sizeof(dp2));
			printf("%d\n", (eexp[n] + MOD - func2(1, 0)) % MOD);
			return 0;
		}
		printf("0\n");
		return 0;
	}
	else if (k2 == 0 || k2 > n) {
		if (k2 == 0) {
			printf("0\n");
			return 0;
		}
		getPi(input1, pi1, k1);

		next1.resize(k1);
		for (int i = 0; i < k1; i++) {
			next1[i].first = next1[i].second = i;

			while (next1[i].first > 0 && input1[next1[i].first + 1] != '0')
				next1[i].first = pi1[next1[i].first];

			if (input1[next1[i].first + 1] == '0')
				next1[i].first++;

			while (next1[i].second > 0 && input1[next1[i].second + 1] != '1')
				next1[i].second = pi1[next1[i].second];

			if (input1[next1[i].second + 1] == '1')
				next1[i].second++;
		}

		memset(dp3, -1, sizeof(dp3));
		printf("%d\n", func3(1, 0));
		/*int t = 0;
		for (int i = 0; i < (1 << n); i++) {
			int tmp = i, cnt = 0, ttmp = 0;
			std::vector<int> ww;
			while (tmp) {
				ww.push_back(tmp % 2);
				tmp /= 2;
			}
			for (int j = ww.size(); j < n; j++) {
				ww.push_back(0);
			}
			bool flag = false;
			for (int j = ww.size() - 1; j >= k1 - 1 && !flag; j--) {
				bool s = true;
				for (int k = 1; k <= k1 && s; k++) {
					if (input1[k] != ww[j - k + 1] + '0')
						s = false;
				}

				if (s)
					flag = true;
			}
			if (flag)
				t++;
		}
		if (t != func3(1, 0))
			printf("!!%d\n", t);*/
	}
	else {
		getPi(input1, pi1, k1);
		getPi(input2, pi2, k2);

		next1.resize(k1);
		next2.resize(k2);

		for (int i = 0; i < k1; i++) {
			next1[i].first = next1[i].second = i;

			while (next1[i].first > 0 && input1[next1[i].first + 1] != '0')
				next1[i].first = pi1[next1[i].first];

			if (input1[next1[i].first + 1] == '0')
				next1[i].first++;

			while (next1[i].second > 0 && input1[next1[i].second + 1] != '1')
				next1[i].second = pi1[next1[i].second];

			if (input1[next1[i].second + 1] == '1')
				next1[i].second++;
		}

		for (int i = 0; i < k2; i++) {
			next2[i].first = next2[i].second = i;

			while (next2[i].first > 0 && input2[next2[i].first + 1] != '0')
				next2[i].first = pi2[next2[i].first];

			if (input2[next2[i].first + 1] == '0')
				next2[i].first++;

			while (next2[i].second > 0 && input2[next2[i].second + 1] != '1')
				next2[i].second = pi2[next2[i].second];

			if (input2[next2[i].second + 1] == '1')
				next2[i].second++;
		}


		memset(dp1, -1, sizeof(dp1));
		memset(dp2, -1, sizeof(dp2));
		printf("%d\n", (func1(1, 0, 0) - func2(1, 0) + MOD) % MOD);
	}
}