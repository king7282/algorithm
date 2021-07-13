#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#define MOD 1000000007

struct node {
	int next[26];
	long long cnt;

	node() {
		memset(next, -1, sizeof(next));
		cnt = 0;
	}
};

std::vector<node> nodeList;
std::string s;
long long dp[200010];

long long solve(int num) {
	if (num == s.size())
		return 1;

	if (dp[num] != -1)
		return dp[num];

	int index = 0, cur = 0;
	dp[num] = 0;

	while (num + index < s.size() && nodeList[cur].next[s[num + index] - 'a'] != -1) {
		cur = nodeList[cur].next[s[num + index] - 'a'];
		dp[num] = (dp[num] + solve(num + index + 1) * nodeList[cur].cnt % MOD) % MOD;
		index++;
	}

	return dp[num];
}

void make_trie(int cur, std::string& input, int index) {
	nodeList[cur].cnt++;

	if (input.size() == index)
		return;

	if (nodeList[cur].next[input[index] - 'a'] == -1) {
		nodeList[cur].next[input[index] - 'a'] = nodeList.size();
		nodeList.push_back(node());
	}

	make_trie(nodeList[cur].next[input[index] - 'a'], input, index + 1);
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n;
	std::cin >> n;
	nodeList.push_back(node());

	for (int i = 0; i < n; i++) {
		std::string input;

		std::cin >> input;
		make_trie(0, input, 0);
	}

	std::cin >> s;
	memset(dp, -1, sizeof(dp));

	printf("%lld\n", solve(0));
}