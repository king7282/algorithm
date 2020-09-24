#include <stdio.h>
#include <algorithm>
 
int input[100010];
 
int last_number(int tmp) {
	int cnt = 0;
	while (tmp) {
		tmp /= 2;
		cnt++;
	}
 
	return cnt;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
 
		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);
 
		std::sort(input + 1, input + 1 + n, [&](int a, int b) {
			return last_number(a) < last_number(b);
		});
 
		long long result = 0;
		int cnt = 0, prev = input[1];
		for (int i = 1; i <= n; i++) {
			if (last_number(prev) == last_number(input[i])) {
				cnt++;
			}
			else {
				result += (long long)(cnt) * (cnt - 1) / 2;
				cnt = 1;
			}
			prev = input[i];
		}
		
		result += (long long)(cnt) * (cnt - 1) / 2;
		printf("%I64d\n", result);
	}
}