#include <stdio.h>
#include <algorithm>
#include <vector>

std::pair<long long, long long> outer[10010], inner[10010], points[300010];
std::vector<long long> X;
bool check[300010];
std::pair<long long, long long> range[300010];

long long aabs(long long num) {
	if (num < 0)
		return -1 * num;
	return num;
}

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &outer[i].first, &outer[i].second);

	for (int i = 0; i < m; i++)
		scanf("%lld %lld", &inner[i].first, &inner[i].second);

	for (int i = 0; i < k; i++) {
		scanf("%lld %lld", &points[i].first, &points[i].second);
		X.push_back(points[i].first);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());
	
	for (int i = 0; i < n; i++) {
		if (outer[i].first < outer[(i + 1) % n].first) {
			int start = std::lower_bound(X.begin(), X.end(), outer[i].first) - X.begin();
			int finish = std::upper_bound(X.begin(), X.end(), outer[(i + 1) % n].first) - X.begin();

			for (int j = start; j < finish; j++) {
				long long tmp1 = (outer[(i + 1) % n].second - outer[i].second) * (X[j] - outer[i].first);
				long long tmp2 = (outer[(i + 1) % n].first - outer[i].first);
				range[j].first = (tmp1 + outer[i].second * tmp2) / tmp2;
				if (range[j].first < 0 && aabs(tmp1) % aabs(tmp2) != 0) {
					range[j].first--;
				}
			}
		}
		else if (outer[i].first > outer[(i + 1) % n].first) {
			int finish = std::upper_bound(X.begin(), X.end(), outer[i].first) - X.begin();
			int start = std::lower_bound(X.begin(), X.end(), outer[(i + 1) % n].first) - X.begin();

			for (int j = start; j < finish; j++) {
				long long tmp1 = (outer[(i + 1) % n].second - outer[i].second) * (X[j] - outer[i].first);
				long long tmp2 = (outer[(i + 1) % n].first - outer[i].first);
				range[j].second = (tmp1 + outer[i].second * tmp2) / tmp2;
				if (range[j].second > 0 && aabs(tmp1) % aabs(tmp2) != 0)
					range[j].second++;
			}
		}
	}

	for (int i = 0; i < k; i++) {
		int index = std::lower_bound(X.begin(), X.end(), points[i].first) - X.begin();
		
		if (range[index].first < points[i].second && points[i].second < range[index].second)
			check[i] = true;
	}

	for (int i = 0; i < X.size(); i++) {
		range[i].first = 1;
		range[i].second = -1;
	}

	for (int i = 0; i < m; i++) {
		if (inner[i].first < inner[(i + 1) % m].first) {
			int start = std::lower_bound(X.begin(), X.end(), inner[i].first) - X.begin();
			int finish = std::upper_bound(X.begin(), X.end(), inner[(i + 1) % m].first) - X.begin();


			for (int j = start; j < finish; j++) {
				long long tmp1 = (inner[(i + 1) % m].second - inner[i].second) * (X[j] - inner[i].first);
				long long tmp2 = (inner[(i + 1) % m].first - inner[i].first);
				range[j].first = (tmp1 + inner[i].second * tmp2) / tmp2;
				if (range[j].first > 0 && aabs(tmp1) % aabs(tmp2) != 0)
					range[j].first++;
			}
		}
		else if (inner[i].first > inner[(i + 1) % m].first) {
			int finish = std::upper_bound(X.begin(), X.end(), inner[i].first) - X.begin();
			int start = std::lower_bound(X.begin(), X.end(), inner[(i + 1) % m].first) - X.begin();

			for (int j = start; j < finish; j++) {
				long long tmp1 = (inner[(i + 1) % m].second - inner[i].second) * (X[j] - inner[i].first);
				long long tmp2 = (inner[(i + 1) % m].first - inner[i].first);
				range[j].second = (tmp1 + inner[i].second * tmp2) / tmp2;
				if (range[j].second < 0 && aabs(tmp1) % aabs(tmp2) != 0)
					range[j].second--;

			}
		}
	}

	for (int i = 0; i < k; i++) {
		if (check[i] == false)
			continue;
		int index = std::lower_bound(X.begin(), X.end(), points[i].first) - X.begin();

		if (range[index].first <= points[i].second && points[i].second <= range[index].second)
			check[i] = false;
	}

	int cnt = 0;
	for (int i = 0; i < k; i++) {
		if (check[i] == false) {
			cnt++;
		}
	}
	
	if (cnt == 0)
		printf("YES\n");
	else
		printf("%d\n", cnt);
}