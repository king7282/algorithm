#include <stdio.h>

bool check[1010];

int func(int num) {
	int result = 0;

	while (num) {
		result += (num % 10) * (num % 10);
		num /= 10;
	}

	return result;
}

int main(void) {
	int n;
	scanf("%d", &n);

	int start = func(n);
	check[start] = true;
	bool flag = true;

	while (start != 1) {
		start = func(start);
		if (check[start] == true) {
			flag = false;
			break;
		}
		check[start] = true;
	}

	if (flag)
		printf("HAPPY\n");
	else
		printf("UNHAPPY\n");
}