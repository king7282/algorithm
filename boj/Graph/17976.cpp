#include <stdio.h>
#include <algorithm>
#include <cstring>

int tree[500010];

int find(int num) {
	if (tree[num] == -1)
		return num;
	return tree[num] = find(tree[num]);
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	int result = 0;
	memset(tree, -1, sizeof(tree));

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a = find(a), b = find(b);
		if (result == 0 && a == b) {
			result = i;
		}
		else if(a != b){
			tree[a] = b;
		}
	}

	printf("%d\n", result);
	
}