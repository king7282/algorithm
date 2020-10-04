
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
 
struct info {
	long long x, y, weight;
	info(long long x, long long y, long long weight) : x(x), y(y), weight(weight) {}
};
 
bool operator<(info a, info b) {
	return a.weight > b.weight;
}
 
std::priority_queue<info> qu;
std::pair<long long, long long> input[100010];
std::vector<long long> X, Y, v[100010], h[100010];
std::vector<std::pair<long long, int>> ttmp;
long long visits[100010];
 
long long aabs(long long num) {
	if (num < 0)
		return -1 * num;
	return num;
}
 
int main(void) {
	long long n, m;
	scanf("%I64d %I64d", &n, &m);
 
	std::pair<long long, long long> start, finish;
 
	scanf("%I64d %I64d %I64d %I64d", &start.first, &start.second, &finish.first, &finish.second);
	for (int i = 1; i <= m; i++) {
		scanf("%I64d %I64d", &input[i].first, &input[i].second);
		X.push_back(input[i].first);
		Y.push_back(input[i].second);
		ttmp.push_back(std::make_pair((input[i].first - 1) * n + (input[i].second - 1), i));
	}
 
	std::sort(ttmp.begin(), ttmp.end());
	std::sort(X.begin(), X.end());
	std::sort(Y.begin(), Y.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());
	Y.erase(std::unique(Y.begin(), Y.end()), Y.end());
 
	for (int i = 1; i <= m; i++) {
		int index1 = std::lower_bound(X.begin(), X.end(), input[i].first) - X.begin(), index2 = std::lower_bound(Y.begin(), Y.end(), input[i].second) - Y.begin();
		
		v[index1].push_back(input[i].second);
		h[index2].push_back(input[i].first);
	}
 
	for (int i = 0; i < X.size(); i++)
		std::sort(v[i].begin(), v[i].end());
 
	for (int i = 0; i < Y.size(); i++)
		std::sort(h[i].begin(), h[i].end());
 
	for (int i = 1; i <= m; i++) {
		visits[i] = std::min(aabs(input[i].first - start.first), aabs(input[i].second - start.second));
		qu.push(info(input[i].first, input[i].second, visits[i]));
	}
 
	while (!qu.empty()) {
		info top = qu.top();
		qu.pop();
 
		int index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((top.x - 1) * n + top.y - 1, 0)) - ttmp.begin();
		if (visits[ttmp[index].second] != top.weight)
			continue;
 
		int index1 = std::lower_bound(X.begin(), X.end(), top.x) - X.begin(), index2 = std::lower_bound(Y.begin(), Y.end(), top.y) - Y.begin();
 
		int vindex = std::lower_bound(v[index1].begin(), v[index1].end(), top.y) - v[index1].begin(), hindex = std::lower_bound(h[index2].begin(), h[index2].end(), top.x) - h[index2].begin();
 
		int prev = std::max(0, vindex - 1), next = std::min(vindex + 1, (int)v[index1].size() - 1);
		int prev_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((top.x - 1) * n + v[index1][prev] - 1, 0)) - ttmp.begin();
		int next_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((top.x - 1) * n + v[index1][next] - 1, 0)) - ttmp.begin();
 
		if (visits[ttmp[prev_index].second] > top.weight) {
			visits[ttmp[prev_index].second] = top.weight;
			qu.push(info(input[ttmp[prev_index].second].first, input[ttmp[prev_index].second].second, top.weight));
		}
 
		if (visits[ttmp[next_index].second] > top.weight) {
			visits[ttmp[next_index].second] = top.weight;
			qu.push(info(input[ttmp[next_index].second].first, input[ttmp[next_index].second].second, top.weight));
		}
 
		prev = std::max(0, hindex - 1), next = std::min(hindex + 1, (int)h[index2].size() - 1);
		prev_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((h[index2][prev] - 1) * n + top.y - 1, 0)) - ttmp.begin();
		next_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((h[index2][next] - 1) * n + top.y - 1, 0)) - ttmp.begin();
 
		if (visits[ttmp[prev_index].second] > top.weight) {
			visits[ttmp[prev_index].second] = top.weight;
			qu.push(info(input[ttmp[prev_index].second].first, input[ttmp[prev_index].second].second, top.weight));
		}
 
		if (visits[ttmp[next_index].second] > top.weight) {
			visits[ttmp[next_index].second] = top.weight;
			qu.push(info(input[ttmp[next_index].second].first, input[ttmp[next_index].second].second, top.weight));
		}
 
		prev = std::max(0, index1 - 1), next = std::min(index1 + 1, (int)X.size() - 1);
		prev_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((X[prev] - 1) * n + v[prev][0] - 1, 0)) - ttmp.begin();
		next_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((X[next] - 1) * n + v[next][0] - 1, 0)) - ttmp.begin();
 
		if (visits[ttmp[prev_index].second] > top.weight + X[index1] - X[prev]) {
			visits[ttmp[prev_index].second] = top.weight + X[index1] - X[prev];
			qu.push(info(input[ttmp[prev_index].second].first, input[ttmp[prev_index].second].second, top.weight + X[index1] - X[prev]));
		}
 
		if (visits[ttmp[next_index].second] > top.weight + X[next] - X[index1]) {
			visits[ttmp[next_index].second] = top.weight + X[next] - X[index1];
			qu.push(info(input[ttmp[next_index].second].first, input[ttmp[next_index].second].second, top.weight + X[next] - X[index1]));
		}
 
		prev = std::max(0, index2 - 1), next = std::min(index2 + 1, (int)Y.size() - 1);
		prev_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((h[prev][0] - 1) * n + Y[prev] - 1, 0)) - ttmp.begin();
		next_index = std::lower_bound(ttmp.begin(), ttmp.end(), std::make_pair((h[next][0] - 1) * n + Y[next] - 1, 0)) - ttmp.begin();
 
		if (visits[ttmp[prev_index].second] > top.weight + Y[index2] - Y[prev]) {
			visits[ttmp[prev_index].second] = top.weight + Y[index2] - Y[prev];
			qu.push(info(input[ttmp[prev_index].second].first, input[ttmp[prev_index].second].second, top.weight + Y[index2] - Y[prev]));
		}
 
		if (visits[ttmp[next_index].second] > top.weight + Y[next] - Y[index2]) {
			visits[ttmp[next_index].second] = top.weight + Y[next] - Y[index2];
			qu.push(info(input[ttmp[next_index].second].first, input[ttmp[next_index].second].second, top.weight + Y[next] - Y[index2]));
		}
	}
 
	long long result = aabs(start.first - finish.first) + aabs(start.second - finish.second);
	for (int i = 1; i <= m; i++) {
		result = std::min(result, visits[i] + aabs(finish.first - input[i].first) + aabs(finish.second - input[i].second));
	}
 
	printf("%I64d\n", result);
}