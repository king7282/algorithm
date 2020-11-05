#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

struct info {
	int x, y, value, left, right;
	info(int x, int y, int value, int left, int right) : x(x), y(y), value(value), left(left), right(right) {}
};

std::vector<info> ladder;
std::pair<int, int> map[52][1010];
bool check[50010];

int main(void) {
	int n, max1 = 0;
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		for (int j = 1; ; j++) {
			int input;
			scanf("%d", &input);
			if (input == 0)
				break;
			ladder.push_back(info(i, j, input, 0, 0));
			max1 = std::max(max1, input);
		}
	}

	std::sort(ladder.begin(), ladder.end(), [](info a, info b) {
		if (a.value == b.value)
			return a.x < b.x;
		return a.value < b.value;
	});

	while (1) {
		std::vector<int> arr;
		arr.push_back(0);
		for (int i = 1; i <= n; i++)
			arr.push_back(i);

		for (int i = 0; i < ladder.size(); i++) {
			if (check[i] == true)
				continue;

			ladder[i].left = arr[ladder[i].x];
			ladder[i].right = arr[ladder[i].x + 1];

			std::swap(arr[ladder[i].x], arr[ladder[i].x + 1]);
		}

		int cnt = 0;
		for (int i = 0; i < ladder.size(); i++) {
			if (check[i] == true)
				continue;
			bool flag = false;
			int index;

			for (int j = i + 1; j < ladder.size() && !flag; j++) {
				if (check[j] == true)
					continue;

				if (ladder[i].left == ladder[j].right && ladder[i].right == ladder[j].left) {
					flag = true;
					index = j;
				}
			}

			if (flag) {
				check[index] = check[i] = true;
				cnt++;
                break;
			}
		}

		if (cnt == 0)
			break;
	}

	int result = 0;
	for (int i = 0; i < ladder.size(); i++) {
		if (check[i] == false)
			result++;
	}

	printf("%d\n", result);

	for (int i = 0; i < ladder.size(); i++) {
		if (check[i] == false)
			printf("%d %d\n", ladder[i].x, ladder[i].y);
	}
}