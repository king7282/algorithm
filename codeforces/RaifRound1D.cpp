#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
 
int input[100010];
std::vector<std::pair<int, int>> result;
 
int main(void) {
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
	}
 
	int cur = n;
	bool flag = true;
	std::queue<std::pair<int, int>> qu, qu2, qu3;
 
	for (int i = n; i >= 1 && flag; i--) {
		if (input[i] == 0)
			continue;
 
		if (input[i] == 1) {
			qu.push(std::make_pair(i, cur));
			result.push_back(std::make_pair(i, cur));
			cur--;
		}
		else if (input[i] == 2) {
			if (qu.size() == 0) {
				flag = false;
				break;
			}
			std::pair<int, int> front = qu.front();
			qu.pop();
			result.push_back(std::make_pair(i, front.second));
			qu2.push(std::make_pair(i, front.second));
		}
		else {
			if (qu3.size() != 0) {
				std::pair<int, int> front = qu3.front();
				qu3.pop();
 
				result.push_back(std::make_pair(i, cur));
				result.push_back(std::make_pair(front.first, cur));
				qu3.push(std::make_pair(i, cur));
				cur--;
			}
			else if (qu2.size() != 0) {
				std::pair<int, int> front = qu2.front();
				qu2.pop();
 
				result.push_back(std::make_pair(i, cur));
				result.push_back(std::make_pair(front.first, cur));
				qu3.push(std::make_pair(i, cur));
				cur--;
			}
			else if (qu.size() != 0) {
				std::pair<int, int> front = qu.front();
				qu.pop();
				result.push_back(std::make_pair(i, cur));
				result.push_back(std::make_pair(front.first, cur));
				qu3.push(std::make_pair(i, cur));
				cur--;
			}
			else
				flag = false;
		}
 
		if (cur == -1)
			flag = false;
	}
 
	if (!flag)
		printf("-1\n");
	else {
		printf("%d\n", result.size());
 
		for (int i = 0; i < result.size(); i++)
			printf("%d %d\n", result[i].second, result[i].first);
	}
}
