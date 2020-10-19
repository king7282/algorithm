#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#define X 255

std::vector<long long> input, words;
std::map<std::string, long long> map;
std::map<long long, long long> map1, map2;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();

	long long cnt = 1;
	while (1) {
		std::string tmp;

		std::cin >> tmp;
		if (tmp == "$")
			break;
		if (map.find(tmp) == map.end())
			map[tmp] = cnt++;
		input.push_back(map[tmp]);
	}

	map.clear();
	cnt = 1;
	while (1) {
		std::string tmp;
		std::cin >> tmp;
		if (tmp == "$")
			break;
		if (map.find(tmp) == map.end())
			map[tmp] = cnt++;
		words.push_back(map[tmp]);
	}

	long long t = 1, hash1 = 0, hash2 = 0, ttmp = 0;
	for (int i = 0; i < words.size(); i++) {
		if (i != 0)
			t *= X;
		hash1 = hash1 * X + input[i];
		hash2 = hash2 * X + words[i];
		ttmp = ttmp * X + 1;
	}
	
	if (hash1 == hash2) {
		bool flag = true;
		for (int i = 0; i < words.size() && flag; i++) {
			if (words[i] != input[i]) {
				flag = false;
			}
		}

		if (flag) {
			printf("1\n");
			return 0;
		}
	}

	bool result = false;
	for (int i = 1; i <= input.size() - words.size(); i++) {
		hash1 = (hash1 - input[i - 1] * t) * X + input[i + words.size() - 1];

		long long tmp = hash2 + (input[i] - words[0]) * ttmp;
		if (hash1 == tmp) {
			bool flag = true;
			int gap = input[i] - words[0];
			for (int j = 0; j < words.size() && flag; j++) {
				if (words[j] + gap != input[i + j])
					flag = false;
			}
			if (flag) {
				printf("%d\n", i + 1);
				result = true;
				break;
			}
		}
	}

	if (!result) {
		for (int i = 0; i <= input.size() - words.size(); i++) {
			map1.clear();
			map2.clear();
			bool flag = true;
			for (int j = 0; j < words.size() && flag; j++) {
				if (map1.find(words[j]) == map1.end() && map2.find(input[i + j]) == map2.end()) {
					map1[words[j]] = input[i + j];
					map2[input[i + j]] = words[j];
				}

				if (map1.find(words[j]) == map1.end() || map1[words[j]] != input[i + j])
					flag = false;
			}

			if (flag) {
				printf("%d\n", i + 1);
				result = true;
				break;
			}
		}

		if (!result)
			while (1);
	}
}
