#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>
#define SIZE 524288

std::vector<int> photoes[1010], X;
int tree1[SIZE * 2 + 1], tree2[SIZE * 2 + 1];

void update1(int num, int val) {
	num |= SIZE;
	tree1[num] = val;

	while (num >>= 1)
		tree1[num] = std::max(tree1[num << 1], tree1[num << 1 | 1]);
}

int query1(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;
	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree1[s]);
		if (e % 2 == 0) r = std::max(r, tree1[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

void update2(int num, int val) {
	num |= SIZE;
	tree2[num] = val;

	while (num >>= 1)
		tree2[num] = std::max(tree2[num << 1], tree2[num << 1 | 1]);
}

int query2(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;

	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree2[s]);
		if (e % 2 == 0) r = std::max(r, tree2[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}



int main(void) {
	int k;
	scanf("%d", &k);

	for (int i = 1; i <= k; i++) {
		int n;
		scanf("%d", &n);

		for (int j = 1; j <= n; j++) {
			int a;
			scanf("%d", &a);

			photoes[i].push_back(a);
			X.push_back(a);
		}
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	std::vector<int> result;

	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < photoes[i].size(); j++) {
			photoes[i][j] = std::lower_bound(X.begin(), X.end(), photoes[i][j]) - X.begin();
		}
	}

	for (int i = 1; i <= k; i++) {
		bool flag = false;

		for (int j = 0; j < photoes[i].size(); j++) {
			update1(j, photoes[i][j]);
		}

		memset(tree2, 0, sizeof(tree2));
		for (int j = 0; j < photoes[i].size() - 1 && !flag; j++) {
			int max1 = query1(j + 1, photoes[i].size() - 1);
			
			if (query2(photoes[i][j] + 1, max1 - 1) != 0)
				flag = true;

			update2(photoes[i][j], 1);
		}

		if (flag)
			result.push_back(i);
	}


	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++)
		printf("%d\n", result[i]);
}