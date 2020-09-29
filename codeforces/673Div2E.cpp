#include <stdio.h>
#include <algorithm>
#include <vector>

int input[300010];

int main(void) {
	int n;
	std::vector<std::vector<int>> index[2];
	scanf("%d", &n);

	index[0].push_back(std::vector<int>());

	for (int i = 0; i < n; i++) {
		scanf("%d", input + i);
		index[0][0].push_back(i);
	}

	long long result = 0, x = 0;
	for (int i = 30; i >= 0; i--) {
		index[(i + 1) % 2].clear();
		long long value0 = 0, value1 = 0;
		for (int j = 0; j < index[i % 2].size(); j++) {
			long long cnt0 = 0, cnt1 = 0;

			std::vector<int> tmp0, tmp1;
			for (int k = index[i % 2][j].size() - 1; k >= 0; k--) {
				if ((input[index[i % 2][j][k]] & (1 << i)) == 0) {
					value0 += cnt1;
					cnt0++;
					tmp0.push_back(index[i % 2][j][k]);
				}
				else {
					value1 += cnt0;
					cnt1++;
					tmp1.push_back(index[i % 2][j][k]);
				}
			}


			std::sort(tmp0.begin(), tmp0.end());
			std::sort(tmp1.begin(), tmp1.end());

			if (tmp0.size() != 0) 
				index[(i + 1) % 2].push_back(tmp0);
			if (tmp1.size() != 0)
				index[(i + 1) % 2].push_back(tmp1);
			
		}
		if (value0 >= value1)
			result += value1;
		else {
			result += value0;
			x = (x | (1 << i));
		}
	}

	printf("%I64d %I64d\n", result, x);
}