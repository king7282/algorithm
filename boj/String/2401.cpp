#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>

std::string sinput[510], linput;
int n, dp[100010];
bool check[510][100010];

std::vector<int> getPi(std::string p){
	int m = (int)p.size(), j=0;
	std::vector<int> pi(m, 0); 
	for(int i = 1; i< m ; i++){ 
		while(j > 0 && p[i] != p[j]) 
			j = pi[j-1]; 
		if(p[i] == p[j]) 
			pi[i] = ++j; 
	} 
	return pi; 
} 

std::vector<int> kmp(std::string s, std::string p){
	std::vector<int> ans;
	auto pi = getPi(p);
	int n = (int)s.size(), m = (int)p.size(), j =0;

	for(int i = 0 ; i < n ; i++){ 
		while(j>0 && s[i] != p[j]) 
			j = pi[j-1]; 
		if(s[i] == p[j]){
			if(j==m-1){ 
				ans.push_back(i-m+1);
				j = pi[j];
			}
			else{ 
				j++; 
			}
		}
	}
	return ans; 
}


int func(int num) {
	if (num == linput.size())
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = func(num + 1);
	for (int i = 0; i < n; i++) {
		if (check[i][num]) {
			dp[num] = std::max(dp[num], func(num + sinput[i].size()) + (int)sinput[i].size());
		}
	}

	return dp[num];
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();

	std::cin >> linput;
	std::cin >> n;

	for (int i = 0; i < n; i++) {
		std::cin >> sinput[i];
		if (sinput[i].size() <= linput.size()) {
			std::vector<int> ans = kmp(linput, sinput[i]);

			for (int j = 0; j < ans.size(); j++)
				check[i][ans[j]] = true;
		}
	}

	memset(dp, -1, sizeof(dp));
	std::cout << func(0);
}