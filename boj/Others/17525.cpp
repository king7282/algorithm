#include <stdio.h>
#include <vector>
#include <algorithm>

int input[30], n;
char arr[30];
std::vector<int> cc;

void mk(std::vector<int>& set, std::vector<std::vector<int>>& result, int start, int cnt) {
	if (cnt == 0) {
		result.push_back(std::vector<int>());
		for (int i = 0; i < cc.size(); i++)
			result.back().push_back(cc[i]);
		return;
	}

	for (int i = start; i < set.size(); i++) {
		cc.push_back(set[i]);
		mk(set, result, i + 1, cnt - 1);
		cc.pop_back();
	}
}

std::vector<std::vector<int>> func(std::vector<int> set, std::vector<int> start, std::vector<int> finish, int k) {

	bool fflag = false;
	for (int i = 0; i < start.size(); i++) {
		if (start[i] != finish[i])
			fflag = true;
	}

	if (!fflag) {
		return std::vector<std::vector<int>>();
	}

	std::vector<std::vector<int>> result;
	if (k == 1) {
		result.push_back(start);
		for (int i = 0; i < set.size(); i++) {
			if (start[0] != set[i] && finish[0] != set[i]) {
				std::vector<int> tmp;
				tmp.push_back(set[i]);
				result.push_back(tmp);
			}
		}
		result.push_back(finish);
	}
	else if (set.size() == k + 1) {
		result.push_back(start);
		std::vector<std::vector<int>> tmp;
		cc.clear();
		mk(set, tmp, 0, k);
		for (int i = 0; i < tmp.size(); i++) {
			bool flag1 = false, flag2 = false;
			for (int j = 0; j < tmp[i].size(); j++) {
				if (tmp[i][j] != start[j])
					flag1 = true;
				if (tmp[i][j] != finish[j])
					flag2 = true;
			}

			if (flag1 && flag2)
				result.push_back(tmp[i]);
		}
		result.push_back(finish);
	}
	else {
		int x = -1;
		for (int i = 0; i < set.size(); i++) {
			bool flag1 = false, flag2 = false;
			for (int j = 0; j < start.size(); j++) {
				if (set[i] == start[j])
					flag1 = true;
				if (set[i] == finish[j])
					flag2 = true;
			}
			if (flag1 == true && flag2 == false) {
				x = set[i];
				break;
			}
		}

		std::vector<int> new_set;
		for (int i = 0; i < set.size(); i++)
			if (set[i] != x)
				new_set.push_back(set[i]);

		std::vector<int> Y, Z, new_start;
		for (int i = 0; i < start.size(); i++) {
			if (start[i] != x)
				new_start.push_back(start[i]);
		}

		bool flag = false;
		for (int i = 0; i < k - 1; i++)
			Y.push_back(new_set[i]);

		for (int i = 0; i < Y.size() && !flag; i++) {
			if (Y[i] != new_start[i])
				flag = true;
		}

		if (!flag) {
			Y.back() = new_set.back();
		}

		for (int i = 0; i < new_set.size(); i++) {
			flag = false;
			for (int j = 0; j < Y.size() && !flag; j++) {
				if (new_set[i] == Y[j])
					flag = true;
			}

			if (flag)
				continue;

			std::vector<int> tmp;
			flag = false;
			for (int j = 0; j < Y.size(); j++) {
				if (Y[j] > new_set[i] && !flag) {
					flag = true;
					tmp.push_back(new_set[i]);
				}
				tmp.push_back(Y[j]);
			}

			if (!flag)
				tmp.push_back(new_set[i]);

			flag = false;
			for (int j = 0; j < finish.size() && !flag; j++) {
				if (finish[j] != tmp[j])
					flag = true;
			}

			if (flag) {
				for (int j = 0; j < tmp.size(); j++)
					Z.push_back(tmp[j]);
				break;
			}
		}

		std::vector<std::vector<int>> result1 = func(new_set, new_start, Y, k - 1);
		std::vector<std::vector<int>> result2 = func(new_set, Z, finish, k);

		for (int i = 0; i < result1.size(); i++) {
			result.push_back(std::vector<int>());
			bool flag = false;
			for (int j = 0; j < result1[i].size(); j++) {
				if (x < result1[i][j]) {
					if (!flag)
						result.back().push_back(x);
					flag = true;
				}

				result.back().push_back(result1[i][j]);
			}
			if (!flag)
				result.back().push_back(x);
		}

		for (int i = 0; i < result2.size(); i++) {
			result.push_back(result2[i]);
		}
	}

	return result;
}

int main(void) {
	int k;
	scanf("%d %d", &n, &k);
	getchar();

	std::vector<int> set;
	for (int i = 1; i <= n; i++) {
		char c;
		scanf("%c", &c);
		arr[i] = c;
		input[c - 'a'] = i;
		set.push_back(i);
	}
	getchar();

	std::vector<int> start, finish;
	for (int i = 1; i <= k; i++) {
		char c;
		scanf("%c", &c);
		start.push_back(input[c - 'a']);
	}
	getchar();

	for (int i = 1; i <= k; i++) {
		char c;
		scanf("%c", &c);
		finish.push_back(input[c - 'a']);
	}

	std::vector<std::vector<int>> result = func(set, start, finish, k);

	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			printf("%c", arr[result[i][j]]);
		}
		if (i != result.size() - 1)
			printf(" ");
	}
}