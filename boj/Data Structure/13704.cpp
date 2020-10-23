#include <stdio.h>
#include <algorithm>

struct info {
	int x, y, index;
};

long long result[100010];
int input[100010], sum[2000010], pq = 1000;
info qu[100010];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	input[0] = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		input[i] = (input[i - 1] ^ a);
		if (input[i] > 2000000)
			while (1);
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		qu[i].x = a;
		qu[i].y = b;
		qu[i].index = i;
	}

	std::sort(qu + 1, qu + 1 + q, [&](info a, info b) {
		if (a.x / pq == b.x / pq)
			return a.y < b.y;
		return a.x / pq < b.x / pq;
	});
	
	for (int i = qu[1].x; i <= qu[1].y; i++) {
		result[qu[1].index] += sum[(input[i] ^ k)];
		sum[input[i]]++;
	}

	for (int i = 2; i <= q; i++) {
		result[qu[i].index] = result[qu[i - 1].index];
		if (qu[i - 1].y < qu[i].y) {
			for (int j = qu[i - 1].y + 1; j <= qu[i].y; j++) {
				result[qu[i].index] += sum[(input[j] ^ k)];
				sum[input[j]]++;
			}
		}
		else {
			for (int j = qu[i - 1].y; j > qu[i].y; j--) {
				sum[input[j]]--;
				result[qu[i].index] -= sum[(input[j] ^ k)];
			}
		}

		if (qu[i - 1].x < qu[i].x) {
			for (int j = qu[i - 1].x; j < qu[i].x; j++) {
				sum[input[j]]--;
				result[qu[i].index] -= sum[(input[j] ^ k)];
			}
		}
		else {
			for (int j = qu[i - 1].x - 1; j >= qu[i].x; j--) {
				result[qu[i].index] += sum[(input[j] ^ k)];
				sum[input[j]]++;
			}
		}
	}

	for (int i = 1; i <= q; i++) {
		if (i == q)
			printf("%lld", result[i]);
		else
			printf("%lld\n", result[i]);
	}
}