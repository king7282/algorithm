#include <stdio.h>
#include <queue>
#define SIZE 262144
 
int tree[SIZE * 2 + 1];
char input[200010], result[200010];
std::queue<int> str[100];
 
void update(int num, int val) {
	num |= SIZE;
	tree[num] += val;
	while (num >>= 1)
		tree[num] = tree[num << 1] + tree[num << 1 | 1];
}
 
int query(int s, int e) {
	s |= SIZE, e |= SIZE;
 
	int r = 0;
	while (s <= e) {
		if (s % 2 == 1) r += tree[s];
		if (e % 2 == 0) r += tree[e];
 
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}
 
int main(void) {
	int n;
	scanf("%d", &n);
	getchar();
	
	for (int i = 1; i <= n; i++) {
		scanf("%c", input + i);
		result[n - i + 1] = input[i];
		str[input[i] - 'a'].push(i);
	}
 
	long long r = 0;
	for (int i = 1; i <= n; i++) {
		int front = str[result[i] - 'a'].front();
		str[result[i] - 'a'].pop();
 
		r = r + (long long)(front - query(1, front) - 1);
		update(front, 1);
	}
 
	printf("%I64d\n", r);
}