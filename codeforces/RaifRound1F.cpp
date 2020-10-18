#include <stdio.h>
#include <list>
#include <algorithm>
#include <climits>
#define SIZE 524288

int tree[SIZE * 2 + 1];
int change[500010];
std::list<int> sum[500010];
char input[500010];

void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;
	while (num >>= 1)
		tree[num] = std::min(tree[num << 1], tree[num << 1 | 1]);
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = INT_MAX / 2;

	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree[s]);
		if (e % 2 == 0) r = std::min(r, tree[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);
	getchar();

	long long prev = 0, result = 0;
	int s = 0, max1 = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%c", input + i);

		if (input[i] == '1')
			s++;
		else
			s = 0;

		max1 = std::max(max1, s);
		prev = prev + max1;
	}

	max1 = s = 0;
	for (int i = n; i >= 1; i--) {
		if (input[i] == '1') {
			s++;
		}
		else {
			sum[s].push_front(i + 1);
			change[i + 1] = s;
			s = 0;
		}

		max1 = std::max(max1, s);
	}

	if (s != 0) {
		sum[s].push_front(1);
		change[1] = s;
	}
	

	for (int i = 0; i <= max1; i++) {
		if (sum[i].size() > 0)
			update(i, sum[i].front());
		else
			update(i, n + 1);
	}

	result += prev;
	for (int i = 1; i < n; i++) {
		if (input[i] == '1') {
			prev -= 1;
			int len = change[i];
			sum[len].pop_front();
			if (sum[len].size() > 0) {
				update(len, sum[len].front());
			}
			else {
				update(len, n + 1);
			}

			int last = std::min(query(len, max1) + len - 2, n);
			prev -= last - i;

			if (len > 1) {
				change[i + 1] = len - 1;
				sum[len - 1].push_front(i + 1);
				update(len - 1, i + 1);
			}

		}
		result += prev;
	}

	printf("%I64d\n", result);
}