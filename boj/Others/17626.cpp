#include <stdio.h>
#include <algorithm>

int limits = 224, n;
int result = 4;

void func(int num, int cnt, int start) {
	if (cnt >= result)
		return;
	if (num == n) {
		result = std::min(result, cnt);
		return;
	}

	for (int i = start; i <= limits && i * i + num <= n; i++) {
		func(num + i * i, cnt + 1, i);
	}
}

int main(void) {
	scanf("%d", &n);

	func(0, 0, 1);
	printf("%d\n", result);
}