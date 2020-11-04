#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#define SIZE 2048

struct info {
	long long lsum, rsum, maxsum, sum;
	info(long long lsum = 0, long long rsum = 0, long long maxsum = 0, long long sum = 0) : lsum(lsum), rsum(rsum), maxsum(maxsum) {}
};

std::pair<int, int> input1[1010], input2[1010];
long long map[2020][2020], hap[2020];
std::vector<std::pair<int, int>> points[2020];
info tree[SIZE * 4 + 1];

void update(int num, info val) {
	num |= SIZE;
	tree[num] = val;
	while (num >>= 1) {
		info &a = tree[num << 1], &b = tree[num << 1 | 1];
		info &result = tree[num];
		result.maxsum = std::max({ a.maxsum, b.maxsum, a.rsum + b.lsum });
		result.sum = a.sum + b.sum;
		result.lsum = std::max(a.lsum, a.sum + b.lsum);
		result.rsum = std::max(b.rsum, b.sum + a.rsum);
	}
}



int main(void) {
	int n1, n2;
	scanf("%d", &n1);
	std::vector<int> X, Y;
	for (int i = 1; i <= n1; i++) {
		scanf("%d %d", &input1[i].first, &input1[i].second);
		X.push_back(input1[i].first);
		Y.push_back(input1[i].second);
	}

	scanf("%d", &n2);
	for (int i = 1; i <= n2; i++) {
		scanf("%d %d", &input2[i].first, &input2[i].second);
		X.push_back(input2[i].first);
		Y.push_back(input2[i].second);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());
	std::sort(Y.begin(), Y.end());
	Y.erase(std::unique(Y.begin(), Y.end()), Y.end());

	long long c1, c2;
	scanf("%lld %lld", &c1, &c2);

	for (int i = 1; i <= n1; i++) {
		input1[i].first = std::lower_bound(X.begin(), X.end(), input1[i].first) - X.begin();
		input1[i].second = std::lower_bound(Y.begin(), Y.end(), input1[i].second) - Y.begin();
		points[input1[i].first].push_back(std::make_pair(input1[i].second, c1));
	}

	for (int i = 1; i <= n2; i++) {
		input2[i].first = std::lower_bound(X.begin(), X.end(), input2[i].first) - X.begin();
		input2[i].second = std::lower_bound(Y.begin(), Y.end(), input2[i].second) - Y.begin();
		points[input2[i].first].push_back(std::make_pair(input2[i].second, -1 * c2));
	}

	long long result = LLONG_MIN / 2;
	for (int i = 0; i < X.size(); i++) {
		memset(hap, 0, sizeof(hap));
		memset(tree, 0, sizeof(tree));

		for (int j = i; j < X.size(); j++) {
			for (int k = 0; k < points[j].size(); k++) {
				hap[points[j][k].first] += points[j][k].second;
				info tmp;
				tmp.lsum = tmp.rsum = tmp.sum = tmp.maxsum = hap[points[j][k].first];
				update(points[j][k].first, tmp);
			}

			result = std::max(result, tree[1].maxsum);
			
		}
	}

	printf("%lld\n", result);
}