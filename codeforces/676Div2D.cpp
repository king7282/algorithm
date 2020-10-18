#include <stdio.h>
#include <algorithm>
#include <vector>
 
long long cost[6];
int mov[6][2] = { {1, 1}, {0, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, 0} };
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long a, b;
		scanf("%I64d %I64d", &a, &b);
		std::vector<std::pair<long long, int>> v;
		for (int i = 0; i < 6; i++) {
			long long tmp;
			scanf("%I64d", &tmp);
			v.push_back(std::make_pair(tmp, i));
		}
 
		std::sort(v.begin(), v.end());
		
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < i; j++) {
				for (int k = j + 1; k < i; k++) {
					int nx = mov[v[j].second][0] + mov[v[k].second][0];
					int ny = mov[v[j].second][1] + mov[v[k].second][1];
 
					if (nx == mov[v[i].second][0] && ny == mov[v[i].second][1]) {
						v[i].first = std::min(v[i].first, v[j].first + v[k].first);
					}
				}
			}
 
			cost[v[i].second] = v[i].first;
		}
 
		long long result = 0;
		if (a == 0) {
			if (b < 0) {
				result = -1 * b * cost[4];
			}
			else
				result = b * cost[1];
		}
		else if (b == 0) {
			if (a < 0) {
				result = -1 * a * cost[2];
			}
			else
				result = a * cost[5];
		}
		else {
			if (a > 0 && b > 0) { // 0 1 5
				result = b * cost[1] + a * cost[5];
				result = std::min(result, std::min(a, b) * cost[0] + (b - std::min(a, b)) * cost[1] + (a - std::min(a, b)) * cost[5]);
			}
			else if (a > 0 && b < 0) { // 
				result = a * cost[5] - b * cost[4];
			}
			else if (a < 0 && b > 0) { // 2 3 4
				result = -1 * a * cost[2] + b * cost[1];
			}
			else {
				a *= -1;
				b *= -1;
				result = a * cost[2] + b * cost[4];
				result = std::min(result, std::min(a, b) * cost[3] + (a - std::min(a, b)) * cost[2] + (b - std::min(a, b)) * cost[4]);
			}
		}
 
		printf("%I64d\n", result);
	}
}