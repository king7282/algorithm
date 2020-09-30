#include <stdio.h>
#include <algorithm>

long long input[20];
int n;
long long w, result;

void func(int num, long long cnt, long long cache) {
	if (num == n + 1) {
		if(cnt == 0)
			result = std::max(cache, result);
		return;
	}

	func(num + 1, cnt, cache);
	func(num + 1, 0, cache + cnt * input[num]);
	func(num + 1, cnt + cache / input[num], cache % input[num]);
}

int main(void) {
	scanf("%d %lld", &n, &w);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	func(1, 0, w);
	printf("%lld\n", result);
}