#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

std::vector<std::pair<char, int>> arr;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();

	std::string input;

	std::cin >> input;
	
	char prev = input[0];
	int cnt = 1;

	for (int i = 1; i < input.size(); i++) {
		if (prev == input[i]) {
			cnt++;
		}
		else {

			arr.push_back(std::make_pair(prev, cnt));
			cnt = 1;
		}

		prev = input[i];
	}
	arr.push_back(std::make_pair(prev, cnt));
	if (arr.size() % 2 == 0) {
		printf("0\n");
		return 0;
	}

	int middle = arr.size() / 2;
	int result = arr[middle].second + 1;

	if (result <= 2) {
		printf("0\n");
		return 0;
	}

	bool flag = true;

	for (int i = 1; i <= middle && flag; i++) {
		if (arr[middle - i].first != arr[middle + i].first) {
			flag = false;
		}

		if (arr[middle - i].second + arr[middle + i].second <= 2)
			flag = false;
	}

	if (flag)
		printf("%d\n", result);
	else
		printf("0\n");
}