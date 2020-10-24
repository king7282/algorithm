#include <stdio.h>
#include <vector>
#include <algorithm>
 
std::vector<int> graph[200010];
long long weights[200010], max1;
 
std::pair<long long, bool> func(int num, long long limits) {
	if (graph[num].size() == 0) {
		bool flag = true;
		if (limits - weights[num] < 0)
			flag = false;
		return std::make_pair(limits - weights[num], flag);
	}
 
	long long sum = 0;
	for (int i = 0; i < graph[num].size(); i++) {
		std::pair<long long, bool> tmp = func(graph[num][i], limits);
		if (tmp.second == false)
			return std::make_pair(0, false);
		sum += tmp.first;
		sum = std::min(sum, max1);
	}
 
	bool flag = true;
	if (sum < weights[num])
		flag = false;
 
	return std::make_pair(sum - weights[num], flag);
}
 
int main(void) {
	int n;
	scanf("%d", &n);
 
	for (int i = 2; i <= n; i++) {
		int a;
		scanf("%d", &a);
		graph[a].push_back(i);
	}
 
	long long sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", weights + i);
		sum += weights[i];
	}
 
	max1 = sum;
	long long s = 0, e = sum, r = sum;
 
	while (s <= e) {
		long long mid = (s + e) / 2;
 
		if (func(1, mid).second == true) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}
 
	printf("%I64d\n", r);
}