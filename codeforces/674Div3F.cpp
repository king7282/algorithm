#include <stdio.h>
#include <algorithm>
#include <cstring>
#define SIZE 262144
#define MOD 1000000007
 
long long tree[SIZE * 2 + 1], cnt;
char input[SIZE], mov[5] = {0, 'a', 'b', 'c', '?' };
int n;
 
void update(int num, long long val) {
	num |= SIZE;
	tree[num] = val;
	while (num >>= 1)
		tree[num] = tree[num << 1] + tree[num << 1 | 1];
}
 
long long query(int s, int e) {
	s |= SIZE, e |= SIZE;
	long long r = 0;
	while (s <= e) {
		if (s % 2 == 1) r += tree[s];
		if (e % 2 == 0) r += tree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}
 
long long func(int first, int second, int third) {
	memset(tree, 0, sizeof(tree));
	long long result = 0, sum = 0;
	for (int i = 0; i < n; i++) {
		if (input[i] == mov[third]) {
			result = (result + sum) % MOD;
		}
		if (input[i] == mov[second]) {
			sum = (sum + query(0, i - 1)) % MOD;
		}
		if (input[i] == mov[first]) {
			update(i, 1);
		}
	}
	
	long long tmp = 1, limits = cnt;
 
	if (first == 4)
		limits--;
	if (second == 4)
		limits--;
	if (third == 4)
		limits--;
 
	for (int i = 0; i < limits; i++)
		tmp = (tmp * 3) % MOD;
 
	return (result * tmp) % MOD;
}
 
int main(void) {
	scanf("%d", &n);
	getchar();
 
	for (int i = 0; i < n; i++) {
		scanf("%c", &input[i]);
		if (input[i] == '?')
			cnt++;
	}
 
	long long result = 0;
 
	result = (result + func(1, 2, 3)) % MOD;
	result = (result + func(1, 2, 4)) % MOD;
	result = (result + func(1, 4, 3)) % MOD;
	result = (result + func(4, 2, 3)) % MOD;
 
	result = (result + func(1, 4, 4)) % MOD;
	result = (result + func(4, 2, 4)) % MOD;
	result = (result + func(4, 4, 3)) % MOD;
	result = (result + func(4, 4, 4)) % MOD;
 
	printf("%I64d\n", result);
}