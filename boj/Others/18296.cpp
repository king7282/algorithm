#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct info {
	int l, r, value;
	info(int l, int r, int value) : l(l), r(r), value(value) {}
};

std::map<std::pair<int, int>, int> map;
std::vector<info> nodelist;
std::deque<int> qu1, qu2;
std::string input1, input2;

bool func(char input, std::deque<int>& qu) {
	if (input == 'C') {
		int front = qu.front();
		qu.pop_front();

		qu.push_front(front);
		qu.push_front(front);
		return true;
	}
	else if (input == 'D') {
		qu.pop_front();
		return true;
	}
	else if (input == 'L') {
		int front = qu.front();
		qu.pop_front();
		if (nodelist[front].l != -1) {
			qu.push_front(nodelist[front].l);
			return true;
		}
		return false;
	}
	else if (input == 'P') {
		int front1 = qu.front();
		qu.pop_front();
		int front2 = qu.front();
		qu.pop_front();
		
		if (map.find(std::make_pair(front1, front2)) == map.end()) {
			map[std::make_pair(front1, front2)] = nodelist.size();
			nodelist.push_back(info(front1, front2, -1));
		}

		qu.push_front(map[std::make_pair(front1, front2)]);
		return true;
	}
	else if (input == 'R') {
		int front = qu.front();
		qu.pop_front();

		if (nodelist[front].r != -1) {
			qu.push_front(nodelist[front].r);
			return true;
		}
		return false;
	}
	else if (input == 'S') {
		int front1 = qu.front();
		qu.pop_front();
		int front2 = qu.front();
		qu.pop_front();

		qu.push_front(front1);
		qu.push_front(front2);
		return true;
	}
	else if (input == 'U') {
		int front = qu.front();
		qu.pop_front();

		if (nodelist[front].l != -1 && nodelist[front].r != -1) {
			qu.push_front(nodelist[front].r);
			qu.push_front(nodelist[front].l);
			return true;
		}
		return false;
	}
}

/*bool OK(info *a, info *b) {
	if (a->l == 0 && a->r == 0 && b->l == 0 && b->r == 0) {
		if (a->value == b->value)
			return true;
		return false;
	}
	else if (a->l != 0 && a->r != 0 && b->l != 0 && b->r != 0) {
		bool flag1 = OK(a->l, b->l);
		if (flag1 == false)
			return false;

		bool flag2 = OK(a->r, b->r);
		if (flag1 == true && flag2 == true)
			return true;
		return false;
	}
	else
		return false;
}*/

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();

	std::cin >> input1 >> input2;
	for (int i = 0; i < std::max(input1.size(), input2.size()) * 2; i++) {
		nodelist.push_back(info(-1, -1, i));

		qu1.push_back(nodelist.size() - 1);
		qu2.push_back(nodelist.size() - 1);
	}

	bool flag1 = true, flag2 = true;
	for (int i = 0; i < input1.size() && flag1; i++) {
		flag1 = func(input1[i], qu1);
	}

	for (int i = 0; i < input2.size() && flag2; i++) {
		flag2 = func(input2[i], qu2);
	}

	if (flag1 == false && flag2 == false) {
		printf("True\n");
	}
	else if (flag1 == true && flag2 == true) {
		if (qu1.size() == qu2.size()) {
			bool flag = true;
			while (!qu1.empty() && flag) {
				int front1 = qu1.front(), front2 = qu2.front();
				qu1.pop_front();
				qu2.pop_front();
				
				if (front1 != front2)
					flag = false;
			}

			if (flag)
				printf("True\n");
			else
				printf("False\n");
		}
		else {
			printf("False\n");
		}
	}
	else {
		printf("False\n");
	}
}

