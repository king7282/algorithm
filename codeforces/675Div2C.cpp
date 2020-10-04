#include <iostream>
#include <algorithm>
#include <string>
#define MOD 1000000007
 
long long front[100010];
long long sum[100010];
 
int main(void) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie();
 
	std::string input;
	std::cin >> input;
 
	long long tmp = 1;
	front[0] = 1;
	for (int i = 1; i <= input.size(); i++) {
		tmp = (tmp * 10) % MOD;
		front[i] = (front[i - 1] + tmp) % MOD;
	}
 
	long long cur = 0, index = 1;
	for (int i = input.size() - 1; i >= 0; i--) {
		cur = (cur + (input[i] - '0') * index % MOD) % MOD;
		sum[i] = (sum[i + 1] + cur) % MOD;
		index = (index * 10) % MOD;
	}
 
	long long result = 0;
	cur = 0;
	for (int i = 0; i < input.size(); i++) {
		result = (result + sum[i + 1]) % MOD;
		result = (result + (cur * front[input.size() - 1 - i]) % MOD) % MOD;
		cur = (cur * 10 + input[i] - '0') % MOD;
	}
 
	std::cout << result;
}