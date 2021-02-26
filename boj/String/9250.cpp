#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <queue>

struct node {
	node* next[26];
	bool finish;
	node* fail;

	node() {
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;
		finish = false;
		fail = nullptr;
	}
};

void insertTrie(node *cur, std::string& input, int index){
	if (index == input.size()) {
		cur->finish = true;
		return;
	}

	if (cur->next[input[index] - 'a'] == nullptr) {
		cur->next[input[index] - 'a'] = new node();
	}

	insertTrie(cur->next[input[index] - 'a'], input, index + 1);
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n;
	node *root = new node();

	for (int i = 1; i <= n; i++) {
		std::string input;

		std::cin >> input;
		insertTrie(root, input, 0);
	}

	std::queue<node *> qu;
	qu.push(root);
	root->fail = root;

	while (!qu.empty()) {
		node *front = qu.front();
		qu.pop();

		for (int i = 0; i < 26; i++) {
			if (front->next[i] == nullptr)
				continue;

			if (front == root)
				front->next[i]->fail = root;
			else {
				node *goals = front->fail;

				while (goals != root && goals->next[i] == nullptr)
					goals = goals->fail;

				if (goals->next[i] != nullptr)
					goals = goals->next[i];

				front->next[i]->fail = goals;
			}

			if (front->next[i]->fail->finish == true)
				front->next[i]->finish = true;

			qu.push(front->next[i]);
		}
	}

	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		std::string input;

		std::cin >> input;

		node *cur = root;
		bool result = false;

		for (int j = 0; j < input.size(); j++) {
			if (cur->finish == true) {
				result = true;
				break;
			}

			while (cur != root && cur->next[input[j] - 'a'] == nullptr)
				cur = cur->fail;

			if (cur->next[input[j] - 'a'] != nullptr)
				cur = cur->next[input[j] - 'a'];
		}

		if (cur->finish == true)
			result = true;

		if (result)
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
	}
}