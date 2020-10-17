#include <stdio.h>
 
long long aabs(long long num) {
	if (num < 0)
		return num * -1;
	return num;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long x1, y1, x2, y2;
		scanf("%I64d %I64d %I64d %I64d", &x1, &y1, &x2, &y2);
 
		long long result = 0;
		if (x1 == x2 && y1 == y2) {
			result = 0;
		}
		else if (x1 == x2) {
			result = aabs(y2 - y1);
		}
		else if (y1 == y2) {
			result = aabs(x2 - x1);
		}
		else {
			result = aabs(x2 - x1) + aabs(y2 - y1) + 2;
		}
 
		printf("%I64d\n", result);
	}
}