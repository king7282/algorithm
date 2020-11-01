#include <stdio.h>
#include <algorithm>
#include <vector>

int input[2000010];
std::vector<int> arr;

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);

		std::sort(input + 1, input + 1 + n);
		arr.clear();

		int prev = input[1], cnt = 1;
		for (int i = 2; i <= n; i++) {
			if (input[i] == prev) {
				cnt++;
			}
			else {
				arr.push_back(cnt);
				cnt = 1;
			}
			prev = input[i];
		}

		arr.push_back(cnt);

		std::sort(arr.begin(), arr.end());
		arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
		int result = 0;

		for (int i = 1; i <= arr.back(); i++) {
			bool flag = true;
			for (int j = 0; j < arr.size() && flag; j++) {
				int upper = arr[j] / i;
				if (arr[j] % i != 0)
					upper++;

				if (!((i - 1) * upper <= arr[j] && arr[j] <= i * upper))
					flag = false;
			}

			if (flag)
				result = std::max(result, i);
		}
		
		arr.clear();

		prev = input[1], cnt = 1;
		for (int i = 2; i <= n; i++) {
			if (input[i] == prev) {
				cnt++;
			}
			else {
				arr.push_back(cnt);
				cnt = 1;
			}
			prev = input[i];
		}

		arr.push_back(cnt);

		int r = 0;
		for (int i = 0; i < arr.size(); i++) {
			r += arr[i] / result;
			if (arr[i] % result != 0)
				r++;
		}

		printf("%d\n", r);
	}
}