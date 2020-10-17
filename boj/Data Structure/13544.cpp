#include <stdio.h>
#include <algorithm>
#include <vector>

int input[100010], next[100010], di[100010], sum[110][200010];
int pq = 1000;
std::vector<int> X;

int main(void) {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", input + i);
		di[i] = i / pq;
		next[i] = (di[i] + 1) * pq;
		X.push_back(input[i]);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());
	
	for (int i = 0; i < n; i++) {
		int index = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		sum[di[i]][index]++;
	}

	for (int i = 0; i <= di[n - 1]; i++) {
		for (int j = X.size() - 1; j >= 0; j--)
			sum[i][j] += sum[i][j + 1];
	}

	int q, prev = 0;
	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		int a, b, c, result = 0;
		scanf("%d %d %d", &a, &b, &c);

		a ^= prev;
		b ^= prev;
		c ^= prev;

		a--; b--;
		if (di[a] == di[b]) {
			for (int j = a; j <= b; j++) {
				if (input[j] > c)
					result++;
			}
		}
		else {
			for (int j = a; j < next[a]; j++) {
				if (input[j] > c)
					result++;
			}

			int start = di[a] + 1, finish = di[b] - 1;
			int index = std::lower_bound(X.begin(), X.end(), c) - X.begin();
			
			if (index != X.size()) {
				if (c == X[index])
					index++;

				for (int j = start; j <= finish; j++) {
					result += sum[j][index];
				}
			}

			for (int j = di[b] * pq; j <= b; j++) {
				if (input[j] > c)
					result++;
			}
		}

		printf("%d\n", result);
		prev = result;
	}
}