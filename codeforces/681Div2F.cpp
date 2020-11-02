#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <climits>
#define MOD 998244353
 
bool check[200010];
int index[200010], query[200010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);
		memset(check, false, sizeof(check));
 
		for (int i = 1; i <= n; i++) {
			int a;
			scanf("%d", &a);
			index[a] = i;
		}
 
		for (int i = 1; i <= k; i++) {
			scanf("%d", query + i);
			check[index[query[i]]] = true;
		}
 
		long long result = 1;
		for (int i = 1; i <= k; i++) {
			int left = index[query[i]] - 1, right = index[query[i]] + 1;
			long long cnt = 0;
 
			if (left >= 1 && check[left] == false)
				cnt++;
			if (right <= n && check[right] == false)
				cnt++;
 
			result = (result * cnt) % MOD;
			check[index[query[i]]] = false;
		}
 
		printf("%I64d\n", result);
	}
}