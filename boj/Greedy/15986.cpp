#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#define SIZE 1048576

long long tree[SIZE * 2 + 1], input[SIZE * 2];
int next[SIZE * 2], sparse[SIZE * 2][25];

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void update(int num, long long val) {
	num |= SIZE;
	tree[num] = val;

	while (num >>= 1)
		tree[num] = gcd(tree[num << 1], tree[num << 1 | 1]);
}

long long query(int s, int e) {
	s |= SIZE, e |= SIZE;

	long long r = tree[s];
	while (s <= e) {
		if (s % 2 == 1) r = gcd(r, tree[s]);
		if (e % 2 == 0) r = gcd(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", input + i);
		input[n + i] = input[i];
		update(i, input[i]);
		update(i + n, input[i]);
	}

	if (query(1, n) != 1) {
		for (int i = 1; i <= n; i++)
			printf("0\n");
		return 0;
	}

	update(2 * n + 1, 1);
	long long cur = input[1];
	std::queue<int> upd;

	for (int i = 1; i <= 2 * n; i++) {
		cur = gcd(cur, input[i]);
		upd.push(i);

		if (cur == 1) {
			while (!upd.empty()) {
				int front = upd.front();
				if (query(front, i) == 1) {
					next[front] = i + 1;
					upd.pop();
				}
				else {
					cur = query(front, i);
					break;
				}
			}
		}
	}
	
	while (!upd.empty()) {
		int front = upd.front();
		upd.pop();
		next[front] = 2 * n + 1;
	}
	next[2 * n + 1] = 2 * n + 1;

	for (int i = 0; i <= 20; i++) {
		for (int j = 1; j <= 2 * n + 1; j++) {
			if (i == 0)
				sparse[j][i] = next[j];
			else
				sparse[j][i] = sparse[sparse[j][i - 1]][i - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		int cnt = 0, ttmp = (1 << 21), cur = i;
		for (int j = 20; j >= 0; j--) {
			ttmp /= 2;
			if (sparse[cur][j] > i + n)
				continue;
			cnt += ttmp;
			cur = sparse[cur][j];
		}

		printf("%d\n", cnt);
	}
}

