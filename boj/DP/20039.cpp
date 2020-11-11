#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 524288

int input[500010], tree[2][2][SIZE * 2 + 1];

void update(int index, int cnt, int num, int val) {
	num |= SIZE;
	tree[index][cnt][num] = val;

	while (num >>= 1)
		tree[index][cnt][num] = std::max(tree[index][cnt][num << 1], tree[index][cnt][num << 1 | 1]);
}

int query(int index, int cnt, int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;

	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree[index][cnt][s]);
		if (e % 2 == 0) r = std::max(r, tree[index][cnt][e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);
	std::vector<int> X;
	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		X.push_back(input[i]);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 1; i <= n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
	}

	input[n + 1] = -1;
	int result = 0;

	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				int value = 0;

				if (k == 0) {
					if (j == 0)
						value = query(0, 1, input[i] + 1, X.size() - 1) + 1;
					else
						value = query(1, 1, 0, input[i] - 1) + 1;

					if (value <= 1)
						value = 0;
				}
				else {
					if (j == 0) {
						value = query(0, 1, input[i] + 1, X.size() - 1) + 1;
						value = std::max(value, query(1, 0, 0, input[i] - 1) + 1);
					}
					else {
						value = query(1, 1, 0, input[i] - 1) + 1;
						value = std::max(value, query(0, 0, input[i] + 1, X.size() - 1) + 1);
					}
				}
				update(j, k, input[i], value);
			}
		}

		int tmp = std::max(query(0, 0, input[i] + 1, X.size() - 1), query(1, 0, 0, input[i] - 1)) + 1;
		if (tmp <= 2)
			tmp = 0;
		result = std::max(result, tmp);
	}

	printf("%d\n", result);
}