#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

char input[20], tmp[20], vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
std::vector<std::string> result;

void solve(int cur, int index) {
	if (index == -1) {
		int vcnt = 0, ccnt = 0;
		for (int i = 0; tmp[i] != '\0'; i++) {
			bool flag = false;
			for (int j = 0; j < 5; j++) {
				if (tmp[i] == vowels[j]) {
					vcnt++;
					flag = true;
					break;
				}
			}

			if (!flag)
				ccnt++;
		}

		if(vcnt >= 1 && ccnt >= 2)
			result.push_back(std::string(tmp));
		return;
	}

	if (cur == -1) {
		return;
	}

	tmp[index] = input[cur];
	solve(cur - 1, index - 1);
	solve(cur - 1, index);
}

int main(void) {
	int n, m;
	scanf("%d %d", &m, &n);

	for (int i = 0; i < n; i++) {
		scanf(" %c", input + i);
	}

	std::sort(input, input + n);
	
	tmp[m] = '\0';
	solve(n - 1, m - 1);

	std::sort(result.begin(), result.end());

	for (int i = 0; i < result.size(); i++)
		printf("%s\n", result[i].c_str());
}