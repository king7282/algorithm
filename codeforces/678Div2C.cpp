#include <stdio.h>
#include <vector>
#define MOD 1000000007
 
std::vector<int> arr;
bool check[1010];
long long comb[1010][1010], fac[1010];
 
void func(int x) {
	int left = 0, right = arr.size();
 
	while (left < right) {
		int middle = (left + right) / 2;
		check[middle] = true;
		if (arr[middle] <= x)
			left = middle + 1;
		else
			right = middle;
	}
}
 
int main(void) {
	int n, x, pos;
	scanf("%d %d %d", &n, &x, &pos);
	for (int i = 0; i < n; i++)
		arr.push_back(i);
 
	func(pos);
	arr.clear();
 
	comb[0][0] = comb[1][0] = comb[1][1] = 1;
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= n; i ++) {
		fac[i] = fac[i - 1] * i % MOD;
 
		comb[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
		}
	}
 
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		if (check[i] == true) {
			if (i < pos)
				a++;
			else if(i > pos)
				b++;
		}
	}
 
	long long result = comb[x - 1][a] * comb[n - x][b] % MOD;
	result = (result * fac[a]) % MOD;
	result = (result * fac[b]) % MOD;
	result = (result * fac[n - a - b - 1]) % MOD;
 
	printf("%I64d\n", result);
}