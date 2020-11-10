#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <list>

int sparse[100010][25], backet[100010][300], pq = 400;
int input[100010], next[100010], start[100010];
std::list<int> indexs[100010];
bool check[100010];

int main(void) {
	int n, result = 0;
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
		if (indexs[input[i]].size() == 0) {
			check[i] = true;
			start[input[i]] = i;
		}

		indexs[input[i]].push_back(i);
		backet[input[i]][i / pq]++;
	}

	for (int i = 0; i < X.size(); i++)
		result = std::max(result, (int)indexs[i].size());

	for (int i = 1; i <= n; i++) {
		indexs[input[i]].pop_front();
		if (indexs[input[i]].size() > 0)
			next[i] = indexs[input[i]].front();
		else
			next[i] = start[input[i] + 1];

		if (next[i] < i)
			next[i] = 0;

		int tmp = indexs[input[i] + 1].size(), d = i / pq;
		if (1 / pq == d) {
			for (int j = 1; j <= i; j++) {
				if (input[j] == input[i])
					tmp++;
			}
		}
		else {
			for (int j = 1 / pq; j < d; j++) {
				tmp += backet[input[i]][j];
			}

			for (int j = d * pq; j <= i; j++) {
				if (input[j] == input[i])
					tmp++;
			}
		}

		result = std::max(result, tmp);
	}

	for (int i = 0; i <= 20; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 0)
				sparse[j][i] = next[j];
			else
				sparse[j][i] = sparse[sparse[j][i - 1]][i - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		indexs[input[i]].push_back(i);
		if (check[i] == false)
			continue;

		int r = 0;
		if (input[i] != 0) {
			r += indexs[input[i] - 1].size();
		}

		int cur = i;
		for (int j = 20; j >= 0; j--) {
			if (sparse[cur][j] == 0)
				continue;
			cur = sparse[cur][j];
			r += (1 << j);
		}

		r++;
		if (input[cur] < X.size() - 1) {
			int tmp = input[cur] + 1, d = (cur + 1) / pq;
			if (d != n / pq) {
				for (int j = cur + 1; j < (d + 1) * pq; j++) {
					if (tmp == input[j])
						r++;
				}
				for (int j = d + 1; j <= n / pq; j++)
					r += backet[tmp][j];
			}
			else {
				for (int j = cur + 1; j <= n; j++) {
					if (tmp == input[j])
						r++;
				}
			}

		}
		result = std::max(result, r);
	}

	printf("%d\n", n - result);
}