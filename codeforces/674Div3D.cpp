#include <stdio.h>
#include <set>
 
long long input[200010];
std::set<long long> set;
 
int main(void) {
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%I64d", input + i);
 
	long long sum = 0, result = 0;
	for (int i = 1; i <= n; i++) {
		sum += input[i];
 
		if (sum == 0 || set.find(sum) != set.end()) {
			result++;
			set.clear();
			sum = input[i];
		}
		set.insert(sum);
 	}
 
	printf("%I64d\n", result);
}