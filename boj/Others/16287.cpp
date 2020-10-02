#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

struct info {
	int value, x, y;
	info(int value, int x, int y) : value(value), x(x), y(y) {}
};

int input[50010];
std::vector<info> v;

int main(void) {
	int w, n, min1 = INT_MAX / 2;
	scanf("%d %d", &w, &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		for (int j = 1; j < i; j++) {
			min1 = std::min(min1, input[i] + input[j]);
			v.push_back(info(input[i] + input[j], j, i));
		}
	}

	std::sort(v.begin(), v.end(), [](info a, info b) {
		return a.value < b.value;
	});

	bool flag = false;
	for (int i = 1; i <= n && !flag; i++) {
		for (int j = 1; j < i && !flag; j++) {
			int left = w - input[i] - input[j];
			if (left < min1)
				continue;

			int s = 0, e = v.size() - 1, r = 0;
			
			while (s <= e) {
				int mid = (s + e) / 2;
				if (v[mid].value <= left) {
					s = mid + 1;
					r = std::max(r, mid);
				}
				else
					e = mid - 1;
			}
			
			for (int z = r; z <= r + 2 && z < v.size(); z++) {
				if (v[z].value == left && v[z].y != i && v[z].x != i && v[z].x != j && v[z].y != j) {
					flag = true;
					break;
				}
			}
		}
	}

	if (flag)
		printf("YES\n");
	else
		printf("NO\n");
}